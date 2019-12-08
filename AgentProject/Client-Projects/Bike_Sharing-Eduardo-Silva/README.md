# Bike Sharing

This is a console project developed in the course "Algorithms and Data Structures" (AEDA) at FEUP. 
It is designed to simulate a bike rental/sharing program between users in the same city. 

# Overview

Upon start of the application, the user is greated with a main menu presenting 5 different options which will lead him to a 
specific sub-meu:

![screenshot_1](https://user-images.githubusercontent.com/32617691/41675081-9e8fb1ee-74b9-11e8-90b2-3dae5445a6c6.png)

## 1. Bikes  

![screenshot_2](https://user-images.githubusercontent.com/32617691/41675168-e1601586-74b9-11e8-8645-312e6bdcff6a.png)

This menu allows the user to rent a bike. It first asks for the username to which it should register the rental. After that, the 
user can choose which type of bike he wants to rent:

- Urban
- Simple Urban
- Child
- Racing

After choosing one of these, the system will show the user the distance to the nearest bike station that contains the choosen type 
of bike. If the user agrees, the rental is started immediatly.

## 2. Stations

![screenshot_3](https://user-images.githubusercontent.com/32617691/41675201-f3db437a-74b9-11e8-93ca-07662bcc7abd.png)

The menu containing all the aspects related to the stations. There is another set of options to choose from:

### 1. Search Station

Allows the user to see pertinent information regarding a station specified by the user. This information includes the (X,Y)
coordinates of the station, the maximum capacity, the number of available spots and the amount of bikes available for rental of each
type.

![screenshot_4](https://user-images.githubusercontent.com/32617691/41675236-0a9ea7b4-74ba-11e8-811b-1cbaa189f3c9.png)

### 2. Show Stations

Same as the previous option, but instead lists all the stations alongside with their respective name and information.

### 3. Show nearest station

Displays the name and information regarding the closest station to the user (he must specify his username beforehand).

## 3. Payment

![screenshot_5](https://user-images.githubusercontent.com/32617691/41675274-262a0942-74ba-11e8-95f7-e54b3b25a0d2.png)

Here the user can deal with all monetary transactions regarding his current rental:

### 1. Balance

Shows how much the user has to pay so far (must indicate username).

### 2. Checkout bike

Initates the checking out process. First, it is displayed the nearest station (alongside the respective information) 
with available spots. The user can then choose to checkout there or in another station.

## 4. Options

![screenshot_6](https://user-images.githubusercontent.com/32617691/41675309-43385fe8-74ba-11e8-9f42-6ebfad4b7646.png)

This menu is intended for testing/management purposes, having a whole set of new options:

### 1. Add/Remove member 

Allows for the addition or removal of a member given his name (a member has special discounts).

### 2. Add/Remove station 

Allows for the addition or removal of a bike station. 

In the first case, it is asked for the new 
station's name, (x,y) coordinates and number of available spots. After that the manager can add the various types of bikes to 
the station.

In the second case, the manager needs only to specify the name of the station to remove.

### 3. Fast Forward 

Here we can add various units of time (minutes, hours, days and months) to the current registered date 
for testing purposes.

### 4. Bike Workshop

![screenshot_7](https://user-images.githubusercontent.com/32617691/41675342-5df7aff0-74ba-11e8-9f76-023ee53d58d7.png)

Menu that allows for the management of the various bike parts:

1. Buy bike part - Here the manager can purchase different bike parts given their name, supplier and respective price.

2. Cheapest supplier - Displays the supplier selling a given part with the lowest price.

3. Add or remove Parts - Adds/removes a part given its name, supplier and price.

4. Check suppliers and prices - Lists all the suppliers and respective prices that sell a given part.

### 5. Bike Shop

![screenshot_8](https://user-images.githubusercontent.com/32617691/41675375-75e7a9da-74ba-11e8-8353-3431aeaf1a9a.png)

This is the menu which holds the options regarding the purchase of bikes.

1. Purchase bikes - Here the manager chooses which types of bikes he wants to purchase and the respective quantity.

2. Search Shop - Shows information about a given bike shop (reputation and the number of bikes of each type that it has).

3. Show Top 5 - Shows the top 5 bike shops by reputation and respective information.

![screenshot_9](https://user-images.githubusercontent.com/32617691/41675428-9673c080-74ba-11e8-9115-0edba3cfe3ed.png)

### 6. Bike Destruction

![screenshot_10](https://user-images.githubusercontent.com/32617691/41675468-af1c26f4-74ba-11e8-8162-d33433be4be1.png)

 Menu containing the options regarding the discontinuation of bikes.
 
 1. Schedule bike for destruction - Registers a type of bike for destruction on a specified date.
 
 2. View bikes scheduled for destruction - Shows all bikes scheduled for disposal.
 
![screenshot_11](https://user-images.githubusercontent.com/32617691/41675499-c0023080-74ba-11e8-8789-abad1b5c6885.png)
 
 3. Remove bike from scheduled destruction - Removes a bike from the disposal registers.
 
 ## 5. Save and Exit 
 
 Exits the application, saving all data to local files.
 
 # UML Diagram
 
 ![uml](https://user-images.githubusercontent.com/32617691/41567425-0d94bfb6-7358-11e8-8501-386041b7053b.png)
 
 # Usage:
 
 Just download the Executable folder and run the .exe from there (don't remove the .txt files from the folder).
