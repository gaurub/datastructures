I was busy interviewing some people one day and thought that I hadn't
actually coded up the answers to all the questions I was asking. I knew
the answers conceptually, but I wanted to try to write the answers to all of 
them in C. 

This led me to start on a singly-linked list implementation, which I then decided
was pointless. I changed it to a doubly linked list for fun. I then realized that
I haven't yet seen a C API that is based on the Java Collections Framework specification, 
so thought that was a noble goal.

This is my first attempt at something like that. I will create structures that are defined in the
JCF specs and create both thread-safe and unsafe versions of them. This should be fun!

Some Milestones (can also be inferred from commits):
1) 31/12/2012: Doubly linked list completed; need to work on tests for this.
2) 2/1/2013: Started work on the Hashtable (Map) implementation; need some serious reading for this one.
3) 4/1/2013: Started integrating pull requests here.
4) 4/1/2013: First pull request accepted!
