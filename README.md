# TEJ4M1-quadruped

This is a final project I made for my grade 12 robotics course (Ontario TER4M1) with a partner, Anthony Ferrante. Our goal was to create a quadruped robot that could walk forwards and turn on the spot to a precise heading, so that it could navigate to any specified position in the world by turning and walking.

We designed our robot in two stages. First, we used two hinge joints per leg to allow the robot legs to push the robot forwards. For simplicity, we came up with a 'crawl gait' where only one leg would move at a time (see _Crawl Gait Updated.pdf_). Our greatest challenge was figuring out a leg move order that ensured the center of gravity of the robot was always in the triangle defined by the three legs not moving, so that the robot did not tip over. The result is our first prototype, quadruped_v_1.

Then, we added a third joint at the shoulders to allow the legs to rotate outwards, so that the robot could turn on the spot. Our solution to turn by a certain angle was to first move the feet of the robot one-at-a-time to the rotated position, then straighten the legs to turn the body. With our short legs, this could work up to an angle of about 30 degrees. Determining a formula for the joint angles required to move the legs involved a great deal of trigonometry. Our method is described in _Rotation on the spot.pdf_. The result is our second and final prototype, quadruped_v_2.3.

You can see it in action here, being commanded to move to different positions in the world: https://youtu.be/WdoF99uVFg4

This project was an excellent foray into robotics for me. I also learned C++ to code the robot controller, and interfaced with some of the libraries used in Webots used to control robot components, like the servos in the joints.
