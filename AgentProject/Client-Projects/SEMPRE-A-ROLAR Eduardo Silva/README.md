# SEMPRE A ROLAR
This is a console project developed during my first year in Informatics and Computing Engineering at FEUP, more specifically in the 
Programming course. 
It is supposed to allow the management of a bus company, having in mind individual routes, buses, drivers and their schedules.

## Overview

To use the application, the user first needs to specify the correct files (default lines file is "Linhas.txt" and drivers file
"Condutores.txt"). If the these are valid, the following main menu will appear:

![screenshot_1](https://user-images.githubusercontent.com/32617691/41614275-f64a202e-73ef-11e8-9f39-154854b13945.png)

This is the main point of access to all the functionalities of the program. From here on out we will take a look into each individual option in this and subsequent menus:

### 1. Driver Management

This is where all the aspects related to the drivers are handled.

![screenshot_2](https://user-images.githubusercontent.com/32617691/41614688-064ec2c6-73f1-11e8-9d65-ef5708c6f71e.png)

1. Add a new driver

Adds a new driver to the company given it's ID number, name, maximum number of consecutive hours the driver can work in a day/shift, maximum number of hours the driver can work in a week and the minimum number of hours he has to rest between shifts.

2. Remove a driver

Removes a driver from the system given its ID number.

3. Change a driver

Allows for the customization of each main parameter regarding a specific driver (identified by its ID). These can be the ID itself, his name, shift length, weekly hour limit and minimum rest time.

4. Assign shifts

If the user chooses this option, he is presented with a list of all drivers whith available shifts alongside their available schedule, prompting him to choose one of them. 


![screenshot_3](https://user-images.githubusercontent.com/32617691/41615243-a2018b58-73f2-11e8-865f-2d72699520d6.png)

After that, it is displayed a list with all the bus lines that aren't full yet as well as the respective schedules, prompting the user to choose one.

![screenshot_4](https://user-images.githubusercontent.com/32617691/41615381-ff542126-73f2-11e8-80f2-b19850704a4f.png)

Finally, the user must then indicate the ay of the week of the new shift, as well as starting and ending time.

5. Remove a shift

Removes a shift from a specific driver (identified by its ID), indicated by the day of the week and starting time.

### 2. Line Management

Englobes the options regarding the different bus routes/lines.

![screenshot_5](https://user-images.githubusercontent.com/32617691/41615677-ce2b04e2-73f3-11e8-8194-52181ea268a2.png)

1. Add a new route

Used to add a new route to the system, given its ID, frequency and the name of at least two stops and the average time it takes to travel from one to another.

2. Remove a route

Removes a route identified by its ID.

3. Change a route

Here the user can customize all the main parameters regarding route (identified by its ID). These can be the ID itself, the frequency. He also can add/remove/change stops as well as correspondent schedules.

### 3. Information

![screenshot_6](https://user-images.githubusercontent.com/32617691/41616049-d3584b36-73f4-11e8-9fce-dc4c9b35bf94.png)

Here the user can see various types of data regarding both the routes and drivers.

1. Schedules and routes

This sub menu contains several other options:

![screenshot_7](https://user-images.githubusercontent.com/32617691/41616319-9b3cca96-73f5-11e8-9503-28d3fc137a6e.png)

The first one shows the user a list of all the routes and respective schedules that include a specified stop.

![screenshot_8](https://user-images.githubusercontent.com/32617691/41616436-ed777720-73f5-11e8-8065-78756e45347b.png)

The second option displays the frequency and schedule of a specified line.

![screenshot_9](https://user-images.githubusercontent.com/32617691/41616571-299e68e4-73f6-11e8-9ec8-608cf6dbd722.png)

The third option gives the user a list of the routes that include a specified stop.

Finally, the fourth option shows the user the stops he has to go by and how much time it will take to go from a stop A to a stop B in the same route.

![screenshot_10](https://user-images.githubusercontent.com/32617691/41616717-8dda2726-73f6-11e8-9960-211fe4126f57.png)

2. Drivers

Here the user can see different aspects regarding the drivers, including a list of the available drivers as well as the shift(s) of a specified driver:

![screenshot_11](https://user-images.githubusercontent.com/32617691/41617263-eeea47d4-73f7-11e8-922d-fb529554cc16.png)

3. Bus

Here the user can see information related to the specific buses on specific routes or a list of unattended shifts.

### 4. Save and Backup Information

The application will close, saving all the changes made into the respective files.

### 5. Restore Previous Information

The system will transfer the information contained in the backup files into the ones being currently used.

### 6. Terminate

The application will exit **without** saving any changes.

## Usage

Just download the Executable folder and run the .exe from there.

**Note:** The .txt files must be in the same folder as the executable.
