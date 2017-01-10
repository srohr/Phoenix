import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.util.*;

public class PHOENIX {
    Labels L = new Labels();

    public final String LINE_LABEL          = "\\s*#pragma PHOENIX_VAR.*";
    public final String LINE_START          = "\\s*#pragma PHOENIX_START.*";
    public final String LINE_CHECKPOINT     = "\\s*#pragma PHOENIX_CHECKPOINT.*";
    public final String LINE_LOOP           = "\\s*#pragma PHOENIX_LOOP.*";
    public final String LINE_OMP            = "\\s*#pragma PHOENIX_OMP.*";
    public final String LINE_PARLOOP        = "\\s*#pragma PHOENIX_PARLOOP.*";
    public final String LINE_CLEANUP        = "\\s*#pragma PHOENIX_CLEANUP.*";

    public final String PHOENIX_INCLUDES         = "#include <fstream>\n" 
                                                + "#include <cstring>\n"
                                                + "#include <stdlib.h>\n"
                                                + "bool PHOENIX_Restore_bool = false;\n"
            ;

    String basefilename = null;

    public static void main(String [] args){
        PHOENIX phoenix = new PHOENIX();
        String infile = args[0];

        //System.out.printf("Operating on file %s\n", infile);
        File input = new File(infile);
        phoenix.basefilename = (input.getName().split("\\."))[0];
        File output = new File(phoenix.basefilename + "_CHECKPOINTING_ENABLED.cpp");

        //Gather labels, store them in program memory.
        //No edits to file made yet.
        phoenix.LabelScanner(input);

        //Create the metaprogrammed file with checkpointing code.
        phoenix.MetaprogramFile(input, output);

        System.out.println(output.getName());

    }

    public boolean LabelScanner(File cppProgram){
        //Initial phase of checkpointer. Gathers list of labels to use in checkpoints and denotes which
        //variables belong in each label (all user defined).

        boolean found_start = false;

        try {
            //Gather labels
            Scanner sc = new Scanner(cppProgram);
            while (sc.hasNext()) {
                String line = sc.nextLine();
                if (line.matches(LINE_LABEL)){
                    L.AddLine(line);
                }
            }

            //Mark OMP labels, mark labels with a start statement
            sc = new Scanner(cppProgram);
            while (sc.hasNext()) {
                String line = sc.nextLine();
                if (line.matches(LINE_START)){
                    String [] s = line.trim().split("\\s+");
                    String label = s[2];
                    //System.out.printf("Found label %s\n", label);
                    for (Labels.Label l : L.vLabels){
                        //System.out.printf("\t%s == %s ?", label, l.name);
                        if (l.name.equals(label)){
                            //System.out.print("\tYES\n");
                            l.started = true;

                            if (!found_start) {
                                l.firstStarted = true;
                                found_start = true;
                            }

                            break;
                        }
                        //else System.out.print("\tNO\n");
                    }
                }
                if (line.matches(LINE_OMP) || line.matches(LINE_PARLOOP)){
                    String [] s = line.trim().split("\\s+");
                    String label = s[2];
                    for (Labels.Label l : L.vLabels) {
                        if (l.name.equals(label)) {
                            l.isOMP = true;
                            break;
                        }
                    }
                }
            }

            return true;
        } catch (FileNotFoundException e) {
            e.printStackTrace();
            return false;
        }
    }

    public boolean MetaprogramFile(File input, File output){
        try {
            //Begin a new file.
            output.createNewFile();

            //Declare IO tools
            Scanner sc = new Scanner(input);
            BufferedWriter fw = new BufferedWriter(new FileWriter(output));

            //Include some libraries we will be needing.
            fw.write(PHOENIX_INCLUDES);

            while (sc.hasNext()) {
                String line = sc.nextLine();
                String addline = null;
                //System.out.println(line);

                if (line.matches(LINE_LABEL)) {
                    //Do nothing.
                }
                else if (line.matches(LINE_START)){
                    addline = MP_START(line);
                }
                else if (line.matches(LINE_CHECKPOINT)){
                    addline = MP_CHECKPOINT(line, sc);
                }
                else if (line.matches(LINE_LOOP)){
                    addline =  MP_CHECKPOINT_LOOP(line, sc);
                }
                else if (line.matches(LINE_OMP)){
                    addline = MP_CHECKPOINT_OMP(line, sc);
                }
                else if (line.matches(LINE_PARLOOP)){
                    addline = MP_CHECKPOINT_OMP_LOOP(line, sc);
                }
                else if (line.matches(LINE_CLEANUP)){
                    addline = MP_KILLBACKUPS(line);
                }
                else{
                    //Not one of our things. Transcribe it faithfully.
                    addline = line;

                }

                if (addline != null && !addline.trim().equals("")) {
                    fw.write(addline);
                    fw.newLine();
                }

            }

            fw.close();

        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }

        return false;
    }

    Labels.Label getLabel (String s){
        Labels.Label lptr = null;

        for (Labels.Label l : L.vLabels){
            if (l.name.equals(s)){
                lptr = l;
                break;
            }
        }
        return lptr;
    }

    String GetCstringName(String fname, String label){
        return "PHOENIX_" + fname + "_" + label + "_cstr";
    }

    String GetDirectoryName(String fname){
        return "PHOENIX_" + fname + "/";
        //return "";
    }

    //Notice to the reader/future maintainers:
    //Functions preceeded by "MP_" return lines of C++ code to be inserted in the resultant output file.
    //MP stands for metaprogramming.

    String MP_Declare_and_strcat_Backup(String label, boolean omp, String fname){
        String ret = null;
        fname.replace(".", "_");
        if (!omp) {
            ret = "\tchar " + GetCstringName(fname, label) + " [100] = \"\";\n"
                    + "\tstrcat(" + GetCstringName(fname, label) + ", \"" + GetDirectoryName(fname) + "\");\n"
                    + "\tstrcat(" + GetCstringName(fname, label) + ", \"" + "backup_" + fname + "_" + label + ".txt" + "\");\n";
        }
        else{
            ret = "\tchar " + GetCstringName(fname, label) + " [100] = \"\";\n"
                    + "\tstrcat(" + GetCstringName(fname, label) + ", \"" + GetDirectoryName(fname) + "\");\n"
                    + "\tstrcat(" + GetCstringName(fname, label) + ", \"" + "backup_" + fname + "_" + label + "_\");\n"
                    //cstring = cstring + "_" + omp_thread_num + ".txt"
                    + "\tsprintf(" + GetCstringName(fname, label) + ", \"%s%d.txt\", " + GetCstringName(fname, label) + ", omp_get_thread_num());\n";
        }

        return ret;
    }

    public String MP_START(String line){
        //Generate code to jump to restorepoint.
        String ret = null;

        //Format: #pragma PHOENIX_START <LABEL>
        String [] s = line.trim().split("\\s+");
        String label = s[2];

        Labels.Label lptr = getLabel(label);

        if (lptr != null) { //This label exists
            //Check if there exists a backup file for this label (case restore)


            String backupName = GetCstringName(basefilename, lptr.name);
            String ifstreamvar = "PHOENIX_" + basefilename + "_ifstream_var";
            ret = "\n{\n";
            if (lptr.firstStarted)
                ret += "\tsystem(\"mkdir -p " + GetDirectoryName(basefilename) + "\");\n";


            ret += MP_Declare_and_strcat_Backup(lptr.name, lptr.isOMP, basefilename)
                + "\tstd::ifstream " + ifstreamvar + ";\n"
                + "\t" + ifstreamvar + ".open(" + backupName + ");\n"
                + "\tif (" + ifstreamvar + ") " + "goto " + label + ";"
                + "\n}\n"
            ;
        }
        else{ //Label does not exist. Raise error.

        }

        return ret;
    }

    public String MP_KILLBACKUPS(String line){
        return "\tsystem(\"rm -rf " + GetDirectoryName(basefilename) + "\");\n";
    }

    public String MP_CHECKPOINT(String line, Scanner sc){
        //Parse the pragma line and generate the appropriate checkpoint code
        String ret = null;

        //Format: #pragma PHOENIX_CHECKPOINT <LABEL>
        String [] s = line.trim().split("\\s+");
        String label = s[2];

        Labels.Label lptr = getLabel(label);

        if (lptr != null) { //This label exists
            //Checkpointing is an if/else. 
            //The if is the restore case and should be unreachable except with goto.
            String ifstreamvar = "PHOENIX_" + basefilename + lptr.name + "_ifstream_var";
            String ofstreamvar = "PHOENIX_" + basefilename + lptr.name + "_ofstream_var";

            ret = "if (false) {\n" //Impossible. Thus only reachable through goto label.
                + "\t" + lptr.name + ":\n"
                + lptr.MP_RestoreLabel(ifstreamvar)
                + "\t;\n"
                + "}\n"
            ;
            //The else is the backup case and happens whenever we don't restore.
            ret += "else {\n"
                + lptr.MP_BackupLabel(ofstreamvar)
                + "}\n"
            ;
        }
        else{ //Label does not exist. Throw an error.
            
        }
        
        return ret;
    }

    public String MP_CHECKPOINT_LOOP(String line, Scanner sc){
        //Special case of MP_CHECKPOINT in which we checkpoint a normal loop
        //This pragma is placed directly above the loop.
        //So we can count curly braces to determine loop body (important, determines when to checkpoint).

        String ret = null;

        //Format of this line: #pragma PHOENIX_LOOP <LABEL> <CONDITION>
        String [] s = line.trim().split("\\s+", 4); //Everything after label is CONDITION
        String label = s[2];
        String CONDITION = s[3]; //If it doesn't have a 3 their code is broken.

        Labels.Label lptr = getLabel(label);


        if (lptr != null) { //This label exists
            //Need target for goto on restore
            String macroname = "PHOENIX_LOOP_" + lptr.name;
            String ifstreamvar = "PHOENIX_" + basefilename + lptr.name + "_ifstream_var";
            String ofstreamvar = "PHOENIX_" + basefilename + lptr.name + "_ofstream_var";

            ret = "PHOENIX_Restore_bool = false;\n"
                + "if (false) {\n"
                + "\t" + lptr.name + ":\n" //Label for goto
                + "\tPHOENIX_Restore_bool = true;\n"
                + "}\n"
            ;

            //Need to find the loop body now, that's where checkpointing code occurs.
            //We find loop body by scanning lines to find the loop (for, while or do while),
            //then by counting curly braces.
            //Hard bit is we need to handle many cases.

            //Case isOMP we must also find the omp pragma and ensure the restore bool is PRIVATE.
            boolean loopHadCurlyBrace = false;
            boolean loopOpen = false;
            int curlyOpenCount = 0;
            String remainingCode = "";

            while (sc.hasNext() && !(loopOpen && curlyOpenCount > 0)) {
                String l = sc.nextLine();
                //Case OMP -
                //Check if this is pragma line.
                //If so, make the bool private.
                if (lptr.isOMP && l.matches("\\s*#pragma\\s+omp\\s+(for|parallel).*")){
                    //Already has private field
                    if (l.matches(".*firstprivate\\s*(.*).*")){
                        String [] sta = l.split("firstprivate\\s*\\Q(\\E", 2);
                        ret += sta[0]
                            + " "
                            + "firstprivate("
                            + "PHOENIX_Restore_bool, "
                            + sta[1]
                            + "\n"
                        ;
                    }
                    //No private field, make one
                    else{
                        String [] sta = l.split("//", 2);
                        ret += sta[0]
                            + " "
                            + "firstprivate(PHOENIX_Restore_bool)"
                        ;

                        if (sta.length > 1 && !sta[1].equals("")){
                            ret += "//"
                                + sta[1]
                            ;
                        }

                        ret += "\n";
                    }
                }

                //Case loop not yet open
                else if (curlyOpenCount == 0) {
                    //Case open curly on same line.
                    if (l.matches("\\s*for.*\\Q{\\E.*") ||
                        l.matches("\\s*while.*\\Q{\\E.*") ||
                        l.matches("\\s*do.*\\Q{\\E.*")) {
                        ret += l + "\n";
                        loopOpen = true;
                        loopHadCurlyBrace = true;
                        curlyOpenCount++;
                    }
                    //Case loop start without open curly on same line. Still need to find open curly brace.
                    //Logic dictates it's the next line.
                    else if (l.matches("\\s*for.*") ||
                             l.matches("\\s*while.*") ||
                             l.matches("\\s*do.*")) {
                        ret += l + "\n";;
                        loopOpen = true;
                    }
                    //Case curly brace, maybe followed by other stuff.
                    else if (l.matches("\\s*\\Q{\\E*.")) {
                        String[] stuff = l.split("\\Q{\\E", 2);
                        curlyOpenCount++;
                        loopHadCurlyBrace = true;
                        ret += "\t{\n";
                        if (stuff.length == 2) //There is stuff after the curly brace. Who puts stuff there?!
                            remainingCode += stuff[1] + "\n";;
                    }
                    //Case anything else.
                    //Why aren't they starting the loop yet?! We asked it be the line after the pragma!
                    else {
                        ret += l + "\n";
                    }
                }
            }

            //Add the restore sequence here.
            ret += "if (PHOENIX_Restore_bool){\n";
            ret += lptr.MP_RestoreLabel(ifstreamvar)
                + "\tPHOENIX_Restore_bool = false;\n"
                + "}\n";


            //Now add the backup sequence
            ret += "if (" + CONDITION + ") {\n"
                + lptr.MP_BackupLabel(ofstreamvar)
                + "}\n"
            ;

            //Add back any code that idiot amateurgrammer put directly after the curly brace.
            ret += remainingCode;

            //Rest of loop. Just add it I guess.
            while (sc.hasNext() && curlyOpenCount > 0){
                String l = sc.nextLine();
                if (l.matches(".*\\Q{\\E.*")) //Open brace
                    curlyOpenCount++;

                if (l.matches(".*\\Q}\\E.*")) //Close brace
                    curlyOpenCount--;

                ret += l + "\n";
            }

        }
        else{ //Label does not exist. Throw an error.

        }
        
        return ret;
    }

    public String MP_CHECKPOINT_OMP(String line, Scanner sc){
        return MP_CHECKPOINT(line, sc);
    }

    public String MP_CHECKPOINT_OMP_LOOP(String line, Scanner sc){
        return MP_CHECKPOINT_LOOP(line, sc);
    }

    public class Labels {
        Vector<Label> vLabels = new Vector<Label>();

        public void AddLine(String line){
            line = line.trim();
            String [] sect = line.split("\\{", 3); //Should have 3 fields. (0)Pragma stuff, (1) Labels, (2) Variables

            //Pragma stuff is now nonsense to us. It just says this is a label/variable section.
            //So we get the other stuff:
            String [] lnames = sect[1].replace("{", "").replace("}", "").split("\\s+"); //Labels
            String tmp = sect[2].replace("{", "").replace("}", "");
            //Need to extract any in []s
            Vector<String> vvect = new Vector<String>();
            boolean inArr = false;
            String [] stmp = tmp.split("\\s+");
            String value = "";
            for (String s : stmp){
                if (s.startsWith("[")){
                    inArr = true;
                    value = s;
                }
                else if (s.endsWith("]")){
                    inArr = false;
                    value += " " + s;
                    vvect.add(value);
                    value = "";
                }
                else{
                    if (inArr){
                        value += " " + s;
                    }
                    else{
                        vvect.add(s);
                    }
                }
            }
            String [] vnames = vvect.toArray(new String [vvect.size()]);

            boolean found = false;
            for (String lname : lnames) {
                for (Label l : vLabels) {
                    if (l.name.equals(lname)) {
                        //Same label name. Thus, same label.
                        found = true;
                        //Add everything, then break.
                        l.AddAllToLabel(vnames);
                        break;
                    }
                }

                if (!found) {
                    //Add everything to a new label.
                    Label nl = new Label(lname);
                    nl.AddAllToLabel(vnames);
                    vLabels.add(nl);
                }
            }

        }

        public class Label {
            String name;
            HashSet<PhoenixVar> vars = new HashSet<PhoenixVar>();
            boolean isOMP = false;
            boolean started = false; //Pre-metaprogramming scan will set this to true if start statement found.
                                    //If start statement not found and a checkpoint on this label is attempted,
                                    //we throw an error.
            boolean firstStarted = false;

            public Label(String s){
                name = s;
            }

            public void AddAllToLabel(String [] vnames) {
                //Add everything, then break.
                for (String variable : vnames) {
                    if (variable.matches("\\Q[\\E.*\\Q]\\E")) {
                        //Array, form: [name size]
                        String[] newArr = variable.replace("]", "").replace("[", "").split("\\s+");

                        if (newArr.length == 2) { //Array, no offset
                            AddVar(newArr[0], newArr[1], "0");
                        }
                        else if (newArr.length == 3) { //Array, offset
                            AddVar(newArr[0], newArr[1], newArr[2]);
                        }
                    }
                    else { //Normal variable
                        AddVar(variable, "-1", "-1");
                    }
                }
            }
            
            public String MP_RestoreLabel(String ifstreamvar){
                String ret = null;

                //Dump everything into the file.
                String backupName = GetCstringName(basefilename, name);

                ret = "{\n"
                        + "\tstd::ifstream " + ifstreamvar + ";\n"
                        + MP_Declare_and_strcat_Backup(name, isOMP, basefilename)
                        + "\t" + ifstreamvar + ".open(" + backupName + ");\n"
                ;

                for (PhoenixVar phoenixVar : vars){
                    if (phoenixVar.nsize.equals("-1"))
                        ret += "\t" + ifstreamvar + " >> " + phoenixVar.name + ";\n";
                    else{
                        String finish = phoenixVar.start + " + " + phoenixVar.nsize;
                        ret += "\tfor(int i = " + phoenixVar.start + "; i < " + finish + "; i++)\n";
                        ret += "\t\t" + ifstreamvar + " >> " + phoenixVar.name + "[i];\n";
                    }
                }
                ret += "\t" + ifstreamvar + ".close();\n" +
                    "}\n"
                ;
                
                return ret;
            }

            public String MP_BackupLabel(String ofstreamvar){
                String ret = null;

                //Read everything from the file.
                String backupName = GetCstringName(basefilename, name);

                ret = "{\n"
                    + "\tstd::ofstream " + ofstreamvar + ";\n"
                    + MP_Declare_and_strcat_Backup(name, isOMP, basefilename)
                    + "\t" + ofstreamvar + ".open(" + backupName + ");\n"
                ;
                for (PhoenixVar phoenixVar : vars){
                    if (phoenixVar.nsize.equals("-1"))
                        ret += "\t" + ofstreamvar + " << " + phoenixVar.name + " << std::endl;\n";
                    else{
                        String finish = phoenixVar.start + " + " + phoenixVar.nsize;
                        ret += "\tfor(int i = " + phoenixVar.start + "; i < " + finish + "; i++)\n";
                        ret += "\t\t" + ofstreamvar + " << " + phoenixVar.name + "[i] << std::endl;\n";
                    }
                }
                ret += "\t" + ofstreamvar + ".close();\n" +
                        "}\n"
                ;

                return ret;
            }

            public void AddVar(String n, String s, String s2){
                vars.add(new PhoenixVar(n, s, s2));
            }

            public class PhoenixVar {
                PhoenixVar(String n, String s, String s2){
                    name = n;
                    nsize = s;
                    start = s2;
                }
                String name;
                String nsize; //Non-arrays default to size -1.
                String start; //Non-arrays default to offset -1.
            }
        }
    }
}
