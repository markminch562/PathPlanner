# PathPlanner
Demonstration of Path Planning capabilities for jobs
Still a work in progress, the end goal is for it to be able to load in any black and white png image and use it a a path planning obsical map, and then demonstrate using visuals in openGL between dykstras, A*, and D* Lite 

Things to fix
--GLAD the opengl wrapper library currently only works for my computer build rather than check the constraints of individual users
--Does not run yet for windows
--OpenGL run and displays the png map but the cost map is output to the command line


Current Development Considerations
-- Diffrent efficiency approches to storing data during path planning
-- A* started out using a unordered set to keep track of places already visited but when compared to just storing a array of Bools or Ints it was found that it was much faster in all senarios even when using 4k image sizes
-- Possible performance improvements for pathplanning, 
  1. use bitset instead
  2. use Sparse Matrix instead
  3. use a combination of OctoMaps with both methods above (might be outside scope of this project)
-- Efficency consernce when writing images to the screen
  The current method just updates the texture each loop in efficent on the gpu pipline
    1. look into PBO buffer instead
    2. use things like direct state access using more modern opengl
-- If image OctoMaps are used possibly look into using the opengl mipmap function to create them and send them back to the cpu, or look into other gpgpu languages
-- For displaying a cost map to the screen consider if it should be in color or a topographical representation 
