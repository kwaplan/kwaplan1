# kwaplan))) 1
kwaplan))) 1 is a failed attempt at an enhanced Doom engine for newer multiplayer games. It was supposed made in order to speed up the making of PISC's integrator project.

During the making of kwaplan 1, I discovered many things that could be useful for some other developers.

## FIELDOFVIEW
There is a macro in Doom's code called "FIELDOFVIEW" and it basically squishes or stretches the viewport of the game. However, only terrain is affected; UI and things(or actors) stay where they are. And even more intriguing, the projection of ceilings and floors completely breaks. It could be useful for games of which the purpose is to be confusing. The default value of FIELDOFVIEW is 2048. So, ready to make a Hyperbolica clone?

## Resolution?
The way Doom renders is peculiar to me. I couldn't just up the resolution with SCREENHEIGHT and SCREENWIDTH, which wasn't unexpected. However, after some modifications, I could get it to run with both macros set to their double. The problem is that Doom would display at its default 320x200 in the middle of the screen whenever UI was around. Removing UI however with control+-, worked, even if the floor rendered higher up than the ceiling? And of course it'd crash a few seconds afterwards. This made me question whether or not it was actually a good idea to fork id Tech 1 to make a CS clone.