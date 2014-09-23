#Getting Starting with Pebble App Tutorial
A step by step guide to writing a pebble app with custom images, use the tap handler for gestures, change images with time and talk to iOS and android
Months ago I bought my first [pebble watch] (https://getpebble.com/) and I finally had a chance to make my first pebble app during HackTheNorth.  My team built an awesome app called Pandr, a tomagachhi like  iPhone app which grew based on your goals taking information from your wearables.

Since Pebble was completely new to me, there was as slight bit of a learning curve, so this guide is my modest attempt to give a few trips and tricks to save time.  This guide was created by the help of Matthew Hungerford's advice at the hackathon and his smaple code [here] [https://github.com/mhungerford/pebble-firstwatch]

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
-Charged Pebble
-SmartPhone (android or iOS) connected to internet
-Computer connected to internet on same network

##Install the Pebble App
Follow the [official guide to get started with your pebble](https://getpebble.com/getting_started).
Steps include:
Install the pebble app on your device (iOS/Android)
Create an account and sign in
Pair your pebble with the app
Update your pebble

## Getting started witht the SDK

Now that you have your pebble and your phone set up, you can now start with developing your first app.  A great place to start is the [Pebble WatchApp SDK site] (https://developer.getpebble.com/sdk/)
I strongly recommend the CloudPebble IDE mostly because I am lazy and used it instead of downloading the SDK and it worked fine for me :).	
Once you have the ide open, you can now get stated with the sdks at the  bottom of the page for[iOS] (https://github.com/pebble/pebble-ios-sdk) and [Android] (https://github.com/pebble/pebble-android-sdk).  If you like reading and setting things up step by step, I would recommend you go ahead an read the guides and they explain things very well then come back here (I will wait for you). If you like to do things by jumping in and hacking, lets get started.

## Important things before we start:

If you didn't already, you need to enable developer connection on the app (settings->developer options)

To use the cloud ide, ensure both the pebble and the computer are on the same network

Edit the glocal settings (optional)

The global settings for the IDE are at the top.  You can connect to your github account (recommended) and change some settings. I personally like VIM (do not select if you do not know what that is) with a nice monokai theme.  I suggest using spaces with reasonable tab or around 4 for readibilty.  Change the settings for your own needs, or you can keep them for now and play with them later.

Here is mine for reference:
![alt text](https://raw.githubusercontent.com/mrandrewandrade/scratch/master/images/first_pebble_tutorial/1.png "Settings")

Again please do not select vim-like if you do not know what that is.  Just use the default settings if unsure.

#Creating or importing  project:
We are now ready  to start our project.  If you are lazy or want to get an app up and running as soon as possible so you can start hacking, then you import my project with option 1.  I suggest you follow option 2 of starting from scratch so can you learn more, but the choice is yours.

Option 1: Importing my project
You can import [my project from github](https://github.com/mrandrewandrade/first_pebble_tutorial)
-At the top click IMPORT-> IMPORT FROM GITHUB 
-Fill out the project name: FIRST_PEBBLE_TUTORIAL
-Github project: https://github.com/mrandrewandrade/first_pebble_tutorial

![alt text](https://raw.githubusercontent.com/mrandrewandrade/scratch/master/images/first_pebble_tutorial/2.png )

