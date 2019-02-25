# Robotics-Algorithms-and-Control
### Question 1: Is Bug 0 algorithm a good choice for this geometry? Why? Under which assumptions can Bug 0 find the goal?
 
<br> To determine whether the Bug 0 algorithm is good or not? We can use Hierarchical decision-making method to evaluate: We have 3 features to influence our decision-making. 
The goal for each feature is divided into 10 grades (from 1-10)

<br> Above, we can easily get the answer for this question: Bug 0 is a good choice without doubt even if it is not that completeness in some geometry map, but in our map it will leave out some fail point. In the meanwhile, Bug 0 is easy to realize which is very important in MPA. And the robot with bug 0 can quickly run to the goad in a very short traveling length. 
In our assumption, when the robot hits the obstacle, we set it to turn left. If our robot will more back to the same point in this map, it will fail to find the goal in this map. Moreover, if the goal is within the obstacles in this map, it will also fail to find the goal.

### Question 2: Is Bug 1 algorithm guaranteed to find the path to the goal in this geometry? Explain.                            
<br> Yes. 
<br> When the robot hit the wall, it remembers that point and run around the obstacle until it runs back to the point. In that process, the robot can calculate the nearest point to goal in the path. And then robot will run to the nearest point in the minimum way.
<br> Algorithm Bug 2 will traverse each point of the obstacle under our instruction, so the point of  will always be able to move to goal.
<br> So under the assumption given in problem 1, we will guarantee to find the path.  

### Question 3: Under which assumption can Bug 2 algorithm find the goal? Explain. 	
<br> Assumption: For Bug 2 algorithm, it could not let the goal within the obstacles or surrounded by the obstacles. As we have mentioned in our method to achieve the algorithm, the main point is to use angle relationship to evaluate:

<br> The boundary we have to let the Bug 2 algorithm follow the line will not satisfy if we don’t have the assumption.
We know that the completeness of algorithm 2 is higher than before. We can use the way below to do so:
Firstly, the robot turns towards the goad, nd run straight the line. The robot can find the straight line between the goad point and the start point. When robot hits the wall, the robot will turn left and follow the path until it arrive the line between the goad point and the start point. 


