Phoenix is a compilation-phase checkpointing tool which makes use of metaprogramming designed for use in C++ programs
(minimum support is for C++11), with optional support for (most) OpenMP features.

The goal of Phoenix is to provide an easy to use, pragma-based metalanguage which allows for quick and easy
modification to a program which results in checkpointing capabilities, so to make the program more reslient to external
errors.

Should a Phoenix-augmented program detect the presence of a previously generated checkpoint, it will automatically
attempt to restore variable state from said checkpoint and fast-forward execution to that point.

Phoenix makes use of labels, referenced below in the various pragmas. These labels should be thought of as names
for checkpoints- therefore  that one cannot attach one label to multiple checkpoints, and attempting to do so would be
considered an error.

Phoenix offers several pragmas for users to define their checkpointing, examples and explanations of which are available
below:

---

#pragma PHOENIX_START LABEL
    Before checkpointing a label, the user must "start" a label. This defined where the restore and jump occurs on
    program resume after a crash.

    Users should think of labels as regions in their code- this pragma defines the start of that region, and the region
    extends down to the checkpoint pragma associated with the label.

    Starting and checkpointing a label should always occur in the same level of scope. Attempting to checkpoint across
    scope will result in a compiler error as there would then be a goto statement across scopes.

    Likewise, no variables should be declared within a label. Attempts to do so will also be met with a compiler error.

    In the case that the checkpoint occurs in an OMP region, this label should also be in that region.

---

#pragma PHOENIX_VAR {LABELS} {VARIABLES}
	This pragma is used to define variables to be backed up, and under which labels these variables are to be
	checkpointed.

	It should be noted that as this is a metaprogramming language, one may designate a variable to be checkpointed
	before that variable is even declared. PHOENIX_VAR lines are used to define labels, and no code will be inserted at
	the line of this pragma.

	Arrays can be backed up with this method, but require the number of elements to be checkpointed, and optionally the
	starting index (will default to zero). See syntax example below.

	Labels and variables are whitespace delimited, and variable types need not be defined- however, users need be aware
	that the operators << and >> must be defined for all variable types being checkpointed.

	Each label can only be checkpointed at one location in the code. This is to ensure no ambiguity during restores.

	Example:
	#pragma PHOENIX_VAR {cat dog fish} {high low [myarr1 NUM_ELEMENTS] [myarr2 22 5]}
		The above would declare three checkpointing labels- "cat", "dog" and "fish".
		Each of these labels checkpoint the same two variables ("high" and "low") and the same two arrays ("myarr1" and
		"myarr2"). "myarr1" is checkpointed from elements 0 to NUM_ELEMENTS - 1 and "myarr2" is checkpointed from
		elements 5 to 26.


---

#pragma PHOENIX_CHECKPOINT LABEL
	The simplest checkpoint- upon reaching this line, Phoenix will create a checkpoint in the program at the line
	this pragma is found on. This pragma is for use in single threaded regions and outside loops.

	A label is required, which will be used to determine which variables need be checkpointed at this location.

---

#pragma PHOENIX_LOOP LABEL CONDITION
	This checkpoint is for use within loops, and is specifically placed above the loop. While it mostly behaves like
	PHOENIX_CHECKPOINT, this label also requires a boolean condition, which designates when backups should occur.
	CONDITION should be a boolean condition given in C++ and will be transcribed exactly into the generated code.

	The user is reminded to ensure they checkpoint any loop control variables they may be using. If they fail to do
	this, behavior of their program after restoring from a checkpoint will be entirely undefined.

	The user MUST put curly braces on their loops, and the open and close brace CANNOT be on the same line.

---

#pragma PHOENIX_OMP LABEL 
	This checkpoint is for use in regions multithreaded via OpenMP which are not loops. It otherwise behaves very much
	like PHOENIX_CHECKPOINT.

	This pragma makes use of omp_get_thread_num() to determine which thread it is in and create checkpoints for each
	thread. That is to say, checkpointing is done without joining threads. This exists for speed, and means that if one
	is doing inter-thread operations, upoin restoring data should be returned to the correct threads.

---

#pragma PHOENIX_PARLOOP LABEL CONDITION
	This checkpoint is for use in loops within OpenMP parallel regions. It should be noted that this pragma will not
	work on loops parallelized with #pragma omp parallel for due to the way which OpenMP parallelizes loops.

	PHOENIX_PARLOOP is to PHOENIX_LOOP as PHOENIX_OMP is to PHOENIX_CHECKPOINT, and users should thus treat this pragma
	as if it were PHOENIX_LOOP, excepting that this pragma is for use in parallel regions.

	Like PHOENIX_OMP, it makes use of omp_get_thread_num() to ensure that data is returned to the same thread which
	initially checkpointed it.

---

#pragma PHOENIX_CLEANUP
    This pragma will delete any Phoenix generated checkpointing files. It is intended for use at the end of the user's
    program so to prevent runs after a successful run from restoring from a checkpoint.

    Use of this pragma is optional, but users are urged to remember that checkpoints will not be removed until something
    removes them.