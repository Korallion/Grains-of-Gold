# Grains-of-Gold

Alchemical stardew valley game in the beginning dregs of development.
This is a project to help me learn basic game-dev, use of git + github, and test my patience and determination.

## Things I am too dumb to remember

### How the hell do I compile this thing?

There is a Makefile, uh, file that lists some variables and then runs a command with those said variables. That gives instructions to g++ (the compiler) on what to do. The command for running it is <code>make all</code>

## Important details:

- 32x32 base pixel block

## Entity list

- player: user controlled player
- npc: these guys move around on their own
  - friendly
  - enemy
  - neutral
- item: something to be picked up
- world-object: doesn't move (could be interacted with)
- particle: world-object with a lifetime (disappears)

## Plan

- RenderObject -> something that can be rendered, should have all attributed used in rendering
  - texture, render width and height 
- GameObject -> extends RenderObject
    - collision, interaction, inventory, health

These are inheritors of GameObject, extending it in their own way
- WorldObject
    - this doesn't have anything to add, at least not that I know of. So perhaps I will leave it as such
- Item
    - these will be ingredients, usable items, things put into inventories ... is there anything added to this from worldObject? Nope
- Particle
    - adds lifetime, after which it passes away
- Character
    - actors within the game, pcs and npcs, the main driving force of interactions

### Object attribute list

This is past the RenderObject values
- collision events
- interaction (button press) events
- pickup events ??? NOT SURE HERE, I think this is a type of collision event
- Movement
- Health
- Items ? Maybe this is a nuance between player and other entities ?

So, to split or not to split ? I don't want to make a permutation of all combinations (WAAAAY TO MUCH ABSTRACTION)!!!

If we make a heirarchy:
- All have possible collision, interaction, pickup, inventory, and health (and proximity ??)
- Classes (the next builds on the previous):
    - Moving (AI for movement in NPCs), is this frame logic? Maybe could add combat here too.
    - Inventory?

Ahh screw it, let's split
- all of them have a BaseGameObject type
    - collision, interaction, inventory, and health
- world-object -> buildings, landmarks, all that jazz
- item -> specifically not collidable, can be put in inventory ... maybe these are just a type of world-object
- particle -> something that has a set lifetime
- characters:
    - npcs
    - players

### Game plan

I can now render things and have them collide (yay!). The only thing that moves is the player. What other basic things do we need?
- a pause menu
- rooms
- pickup and put down (inventory interaction)
- ui elements (health, stamina)
