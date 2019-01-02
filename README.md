# Castle-Enemy-Simulation

This project is mainly for implementing data structures and algorithms. The castle enemy simulation consists of four towers which belongs to a castle. Every tower is responsible for a certain region were enemies attack the castle and towers have to defend it. <br />
There are four types of enemies:<br />
**1- Fighter enemy in GREEN**: This type of enemies throws fire on the tower causing damage to the tower itself. <br />
**2- Freezer enemy in BLUE**: This type of enemies throws ice on the tower causing ice accumulation on the tower so the tower gets freezed for some time and is not able to fire the enemies for sometime until this ice accumulation becomes less than a certain threshold. <br />
**3- Healer enemy in ORANGE RED**: This type of enemies heals the enemies surrounding it by increasing their health by 30% while losing only 3% of its own health. This type cannot exceed 20% of the total enemy count. <br />
**4- Spy enemy in YELLOW**: This type of enemies attacks other enemies surrounding it while the tower cannot distinguish between between it and other types of enemies so the tower also attack it as a regular enemy.<br />
<br />
Six test cases were generated in .txt files to see whether the game is WIN, LOSR or DRAW. <br />

![alt text](https://github.com/youhanamikhaiel/Castle-Enemy-Simulation/blob/master/Castel-Enemy-Simulation.png)
