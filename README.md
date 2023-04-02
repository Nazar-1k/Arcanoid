# ARCANOID
The mini game is written the library (SDL2)
![image](https://user-images.githubusercontent.com/82716260/229357869-1101af61-a3eb-42a1-a4a2-4568ec8b906c.png)

# About project
Arkanoid is an arcade game in which you have to break blocks with a ball while controlling a paddle-like ship known as the Vaus, the player is tasked with clearing formations of colorful blocks by deflecting the ball towards it without allowing the ball to leave the bottom edge of the playing field. Some blocks contain power-ups that have different effects, such as increasing Vaus' length, creating a few extra bullets, or equipping Vaus with cannons. Other blocks may be indestructible or require multiple hits to break.

# Gameplay

![image](https://user-images.githubusercontent.com/82716260/229361174-5cb9748c-86f5-4962-aa24-acc1d8fe5840.png)

The game starts from the Start menu (see below in the Menu item), when you press any button, the game will start.

Blocks will be generated (blocks are generated in a random color), also if it is 3-4 or 6-10 levels then moving blocks will be generated (they are also generated in a random color). A platform with a bullet is also created in the level.

When we press the spacebar, the game will start and the ball will launch at a random angle upwards.

You need to knock down all the normal blocks to pass the level. Moving blocks can be knocked down with a large ball or a bullet (which fires when you take the Shot option, see below in the Ability), they do not affect the transition to the next level. When we have a small ball and it touches a simple block, the block becomes cracked and can be destroyed the second time.

If level (1-9) is passed, the Start menu appears on the screen again, if level 10 is passed, the win menu appears (see below in the Menu item).

There are also 9 possibilities in the game about each of them in the next section Ability.



# Ability

We have 9 possibilities, of which there are good ones (increasing the platform, creating 2 more balls each on one screen, increasing the ball, decreasing the speed, a red line that does not allow the ball to fall, and shooting mode), as well as bad ones (softening the platform, decreasing the ball , speed increase)

One of these abilities drops randomly (from a block) when a platform is destroyed.

1. 3balls - creates 2 more balls from each one on the screen;
![image](https://user-images.githubusercontent.com/82716260/229361789-e74a59ca-f582-4b54-ab6a-030a2b9c3ed5.png)

Work example:

![image](https://user-images.githubusercontent.com/82716260/229362139-ae622e7c-474f-4bc5-a5b3-7c5c9880f22a.png)


2. Big ball - increases the size of the ball;
![image](https://user-images.githubusercontent.com/82716260/229361701-394229f0-2482-4b10-81c8-4118a61e08e0.png)

Work example:

![image](https://user-images.githubusercontent.com/82716260/229362186-643d64c0-df2e-46d7-9617-37ab659c178b.png)


3. Small ball - reduces the size of the ball;
![image](https://user-images.githubusercontent.com/82716260/229361824-b948450a-f39f-4877-9ebd-6972f9f11862.png)

Work example:

![image](https://user-images.githubusercontent.com/82716260/229362226-75f1d153-cffc-46e6-a2ae-f35fb90af57d.png)

4. Faster speed balls - increases the speed of the ball;
![image](https://user-images.githubusercontent.com/82716260/229361725-0c995280-5df1-4e04-8ce8-35654c781ff2.png)

5. Slowest speed balls - reduces the speed of the ball;
![image](https://user-images.githubusercontent.com/82716260/229361671-7030a58a-31d7-4428-8083-f2c3e89db92a.png)

6. Longest platform - increases the platform;
![image](https://user-images.githubusercontent.com/82716260/229362067-e296c7b3-0655-4610-8410-dbdecd66f2d3.png)

Work example:

![image](https://user-images.githubusercontent.com/82716260/229362091-7320523b-657f-4416-8a89-8a2f98aaf380.png)


7. Shorter platform - reduces the platform;
![image](https://user-images.githubusercontent.com/82716260/229361637-45bb8ef0-c6c2-463e-890d-0f3acd738ee1.png)

Work example:

![image](https://user-images.githubusercontent.com/82716260/229362259-89f2a06a-0280-4d8b-a1c8-836077d71bc7.png)


8. Shot platform - includes shooting mode;
![image](https://user-images.githubusercontent.com/82716260/229361744-48e0eed3-dd9b-4093-8baa-70e07bca7820.png)

Work example:

![image](https://user-images.githubusercontent.com/82716260/229362285-1e7734f6-688c-4d5c-9c71-cec28e6cee83.png)


9. Redline - Creates a red line from which the ball bounces.
![image](https://user-images.githubusercontent.com/82716260/229361768-6018dcfe-59bd-40ab-aca4-591b92a818d2.png)

Work example:

![image](https://user-images.githubusercontent.com/82716260/229362321-49764c79-bc03-469f-919c-1f8e096b79aa.png)

# UI

The user interface contains the number of lives on the left side, the stop game button and the level the user is currently on

![image](https://user-images.githubusercontent.com/82716260/229359647-c79b01f2-817c-4305-8169-073518bc1d73.png)


# Levels

The game has 10 unique levels and the higher the level, the more difficult it is to complete.

![levels](https://user-images.githubusercontent.com/82716260/229358467-baaac758-041e-446d-8131-8850c7e5fb3e.png)

# Menu

Start menu:

![image](https://user-images.githubusercontent.com/82716260/229358653-b179acbf-2e12-4b2b-8737-babe04298b09.png)

Stop menu:

![image](https://user-images.githubusercontent.com/82716260/229358706-c52d07c4-db80-4888-8ed2-24773b4e0d09.png)

Game over:

![image](https://user-images.githubusercontent.com/82716260/229358739-809ac186-9141-4b02-b20f-da9e03365ebb.png)

WIN Menu:

![image](https://user-images.githubusercontent.com/82716260/229359084-07356100-6050-49f5-ad8e-f80e4720a657.png)


# Enjoy yourself
