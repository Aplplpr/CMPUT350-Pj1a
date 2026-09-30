# CMPUT 350 HW 1

Liam:
I have using ChatGPT to help me analyzing the Task questions, like help me removing useless and meaningless informations, and building bone structure of the programmer. This is very useful, cause too many irrelative informations would affects how we understand the questions, but ai can help us identifying the most important things. And we only need to think how to implement queries

Siqi:
As a team, we used AI to help us plan the division of work so that the two team members could work relatively independently without slowing down the development process. (More details about how we divided the tasks can be found in the issues in our GitHub repository.)
During my individual development process, I used AI to help write documentation and to debug compilation and runtime issues. I also asked AI whether there were more efficient ways to implement certain parts of the code. AI suggested one improvement in the `run()` method of `GameEngine.cpp`: using an in-place compaction method to remove dead objects from the active object vector. Instead of repeatedly erasing elements from a `std::vector`, which can cause O(n^2) shifting in the worst case, the code uses a read index and a write index to move only living objects to the front and then resizes the vector once. This helped me understand a more efficient way to manage object lifecycles in the engine.
Overall, using AI did help me learn new techniques and gave me new ways to think about implementation and problem-solving.
