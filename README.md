#Getting Starting with Pebble App Tutorial
A step by step guide to writing a pebble app with custom images, use the tap handler for gestures, change images with time and talk to iOS and android

Months ago I bought my first [pebble watch] (https://getpebble.com/) and I finally had a chance to make my first pebble app during HackTheNorth.  My team built an awesome app called Pandr, a tomagachhi like  iPhone app which grew based on your goals taking information from your wearables.

Since Pebble was completely new to me, there was as slight bit of a learning curve, so this guide is my modest attempt to give a few trips and tricks to save time.  This guide was created by the help of [Matthew Hungerford's](https://github.com/mhungerford) advice at the hackathon and his sample code [here] (https://github.com/mhungerford/pebble-firstwatch)

This guide goes over how to:
- Turn images in pixel art for the pebble
- Display custom pixel art as a watchface
- Use a simple flick gesture to change images
- Use the time and date to send images
- Send and receive messages from an external source (iOS, Android)

## Background:
I come from a hardware background with some embedded software development experience with C.  This is not to serve as an introduction to C, rather provide you with the necessary information to get an app up and running as soon as possible. Some background reading might be necessary to fully understand what is going on.

For this tutorial I specifically decided not to comment everything line by line, to leave it as an activity for you to complete. I recommend you comment line by line to understand what is going on for yourself, but copying a pasting the source code or forking and hacking away is cool as well.

##Prerequisites required:
- Charged Pebble
- SmartPhone (android or iOS) connected to internet
- Computer connected to internet on same network

##Install the Pebble App
Follow the [official guide to get started with your pebble](https://getpebble.com/getting_started).
Steps include:
- Install the pebble app on your device (iOS/Android)
- Create an account and sign in
- Pair your pebble with the app
- Update your pebble

## Getting started witht the SDK

Now that you have your pebble and your phone set up, you can now start with developing your first app.  A great place to start is the [Pebble WatchApp SDK site] (https://developer.getpebble.com/sdk/) I strongly recommend the [CloudPebble IDE](https://cloudpebble.net/ide/) (open in a new tab) mostly because I am lazy and used it instead of downloading the SDK and it worked fine for me :).	

Once you have the ide open, you can now get stated with the sdks at the  bottom of the page for [iOS] (https://github.com/pebble/pebble-ios-sdk) and [Android] (https://github.com/pebble/pebble-android-sdk).  If you like reading and setting things up step by step, I would recommend you go ahead an read the guides and they explain things very well then come back here (I will wait for you). If you like to do things by jumping in and hacking, lets get started.

## Important things before we start:

- If you didn't already, you need to enable developer connection on the app (settings->developer options)

- To use the cloud ide, ensure both the pebble and the computer are on the same network

- Edit the glocal settings (optional)

The global settings for the IDE are at the top.  You can connect to your github account (recommended) and change some settings. I personally like VIM (do not select if you do not know what that is) with a nice monokai theme.  I suggest using spaces with reasonable tab or around 4 for readibilty.  Change the settings for your own needs, or you can keep them for now and play with them later.

Here is mine for reference:
![alt text](/img/1.png "Settings")

Again please do not select vim-like if you do not know what that is.  Just use the default settings if unsure.

#Creating or importing  project:
We are now ready  to start our project.  If you are lazy or want to get an app up and running as soon as possible so you can start hacking, then you import my project with option 1.  I suggest you follow option 2 of starting from scratch so can you learn more, but the choice is yours.

## Option 1: Importing my project


From the  [CloudPebble IDE](https://cloudpebble.net/ide/) you can import [my project from github](https://github.com/mrandrewandrade/first_pebble_tutorial).  Here is how:
- At the top click IMPORT-> IMPORT FROM GITHUB 
- Fill out the project name: FIRST_PEBBLE_TUTORIAL
- Github project: https://github.com/mrandrewandrade/first_pebble_tutorial

![alt text](/img/2.png )


Alternatively you can download the zip folder for my app [here] (https://github.com/mrandrewandrade/first_pebble_tutorial/archive/master.zip)  and use the upload zip dialog filling out the name and selecting the file.

![alt text](/img/3.png )

Now click import and get started

### Lets get running before we can walk!

If just set up the project with the code and resoruces and want to get it running on your phone, look no further.  Otherwise skip the next couple steps and follow option 2.

Once you added the code, you can click Compilation on the left panel.  Lets add the phone's ip address:

- On your phone open the pebble app, tap the left to open the menu and click developer.  The IP adress of the phone should now show up

- On the CloudIDE at the develper page, add the server IP into cloudpebble which is showing on your phone.

- Click install and run and now you have the app installed an running on your pebble!

Flick your wrist and watch the image change.  Now that its working, its time go get hacking!  You can use the rest of this guide as reference.


## Option 2: Create a project from scratch
If you choose option 2, you are on the right track and should create a new project
![alt text](/img/4.png )


## Turning images into pixel art:

We are now ready to rock and roll.  Instead of writing code, lets have some fun and turn images into beautiful pixel art.  Keep in mind, I am terrible at graphic design, so am not going to do anything fancy.

To get started you can download and install [GIMP - The GNU Image Manipulation Program](http://www.gimp.org/) . Its a free and opensourced project which is very similar to photoshop.  If you can do things faster in photoshop use that.

After downloading and install GIMP, download a sample photo and get started.  For the hackathon and for the sake of this tutorial lets use  a cute panda for the app.  The designer on the team created this asset and shared it with me.  

![alt text](/img/5.jpg )

Lets go ahead and download the image by right clicking this and saving.  Alternatively you can do the same [Here](https://raw.githubusercontent.com/mrandrewandrade/scratch/master/images/pandarough.jpg)


### Using GIMP

After GIMP is intalled, let open the application.  

After opening up gimp, I like to go to:

windows-> enable single-window-mode to single window experience.

Now lets open the photo up in GIMP by navigating to where it was downloaded after going to File-> Open

If a popup comes up about C2 conversion, just click convert

### Fitting to the Pebble screen

The pebble screen is 144×168 pixel so lets get our image to that size.  Go to image-> scale image and lets set the width to 144.  Since the image is about square in this case, this should leave me with some pixels above and below for text such as the time and possible a messages

![alt text](/img/6.jpg)

Now click scale and it should scale to a smaller size

Since the pebble displays black and white, and my panda's body is white, lets make a 1 pixel outline so he remains visable. 

Select the fuzzy select tool by hitting  U or click the wand in the toolbar.  

Next pick the the grey background using the left mouse click

Next lets go to the top menu and click Select-> Invert (or hit ctrl-I on windows) to invert the selection

Edit -> Stroke Selection  and making a solid color 1 px line width.

![alt text](/img/7.png )

Now click stroke and how we have an outline.

Lets remove the rest of the junk left on the image.

Lets hit U  and pick the grey background and click hit the delete key

Lets hit R for the rectangual select tool and drag select those black side bars individually and click delete

Finally we need to convert the image into a back and white png

Lets drag select the full image with the rectangual select tool

Click Colors-> brightness-contrast

Now toggle the brightnes and contast until you get a beautiful black and white image

![alt text](/img/8.png )

You can also play with the brushes and pencil tool to get a better looking image.  For this example, I created a 1 px pencil by setting the square brush to size 0.1 and touched up the nose to my liking

![alt text](/img/9.png )

Now that we have our pixel art, lets export to png.

Lets do this by clicking:

File->Export

Then saving the file to somewhere safe like the desktop as panda_happy.png

I am also going to now use the eraser  and brush to change the panda a little bit to a sad panda and export it as panda_sad.png.  It is your turn to get creative or you can just download my image here:
https://raw.githubusercontent.com/mrandrewandrade/first_pebble_tutorial/master/resources/images/panda_sad.png

We now have some beautiful art we can put on our pebble.

##Adding the images as resources

For this app for the sake of speed (due to limitation of the pebble transmission via bluetooth), lets preload the images into our pebble.  Lets hop back into cloudpebble and start to add the images as resource. 

Click “add new” next to resouces.
Set the resoruce type to “PNG image”
And select panda.png from where you saved it

Now lets name the identifier.  To be verbose with the resource lets start the name IMAGE_ and put PANDA_HAPPY and the end make the identifier IMAGE_PANDA_HAPPY. I like to put IMAGE_ at the front since the resource in an image and I put everything in caps since it is a constant

Once you name the identier click save

Lets repeat the process with IMAGE_PANDA_SAD

By adding the resource we now can access the images by the indentifier.  In our code we can now use the images by calling the load_image_resources(NAME) function.  For example:

load_image_resource(RESOURCE_ID_IMAGE_PANDA_SAD);
load_image_resource(RESOURCE_ID_IMAGE_PANDA_HAPPY);


##Lets get coding

We now have all the requirements, lets get coding.

You can find the source for the [here](https://raw.githubusercontent.com/mrandrewandrade/first_pebble_tutorial/master/src/main.c), it is your job to comment it line by line so you understand what is going on.  Lets get this to build so you can play with it and see the behaviour of the app paired with the code.

Click add new and name it main.c.  You can now copy paste the code from above.

Once you added the code, you can click Compilation on the left.  Lets add the phone's ip address.

On your phone open the pebble app, tab the left to open the menu and click developer.  Now lets add the server IP into cloudpebble which is showing on your phone.

Click install and run and now you have the app installed an running on your pebble!

Flick your wrist and watch the image change.

I am a bit tired now writing this tutorial.  When I get a chance, I will put some more info about each function and some android/iOS code how to send messages.

