# Quick-Prototype

Designed to facilitate rapid game development, our plugin enables the easy setup of essential components such as GameModes, Controllers, Levels, and Characters. The integration of these elements is automated, with the GameMode and Controller being assigned to each level seamlessly. Further workflow enhancements are provided by the asset renaming feature, which allows asset names to be customized and differentiated according to project needs. Ideal for both novice and experienced developers, the building of your game prototype is made smooth and efficient through our tool.

## How to use it?

### 1. Right click on the folder where you wish to create the prototype files and click "Setup Prototype"
![1](https://github.com/user-attachments/assets/f1723390-9312-49ea-b78d-117580502452)


### 3. A window with all the properties pops up
![2](https://github.com/user-attachments/assets/600068ab-7667-40ac-80ef-01292158afb7)

![image](https://github.com/user-attachments/assets/e4a7f6c5-d01a-4e27-84da-04d0e54ce904)

#### Properties
| Property                              | Uses                                                                                                         |
|---------------------------------------|--------------------------------------------------------------------------------------------------------------|
| **Create Level**                      | This will show up a property to add a custom level                                                           |
| **Base Game Mode**                    | This takes in the Base Game Mode that the prototype Game Mode will inherit from                              |
| **Game Mode Should Implement Interface** | Setting this to true will show up an array where the user can add as many interfaces they want the Prototype Game Mode to use in the array |
| **Base Controller**                   | This takes in the Base Controller that the prototype Controller will inherit from                            |
| **Controller Interfaces to Add**      | Setting this to true will show up an array where the user can add as many interfaces they want the Prototype Controller to use in the array |
| **Base Character**                    | This takes in the Base Character that the prototype Character will inherit from                              |
| **Character Interfaces to Add**       | Setting this to true will show up an array where the user can add as many interfaces they want the Prototype Character to use in the array |
| **Dev Name**                          | This will contain the name of the developer. e.g., David                                                     |
| **Focus**                             | This will be the name of the mechanic or system that the developer is going to make with them                |


### 4. And finally click on the Create Button

This will create the following files:

- A Game Mode
- A Controller
- A Character
- A Level (if the Create Level was set to true and the Base Level was set)
![image](https://github.com/user-attachments/assets/55aa3f7e-e0bc-457c-a6db-05d21306d26f)


What will be set up for you??

- The Level will have the Game mode overriden with the prototype Game Mode you just created
![image](https://github.com/user-attachments/assets/10ba771c-248f-44a1-866b-97ca4e305563)

- The Game Mode will have the prototype Controller and the Character that was created during the process
![image](https://github.com/user-attachments/assets/23fb2a0b-24ae-46ea-a544-5c8b19738677)

- All the interfaces will be added to the appropriate blueprints if they were set during the creation
![image](https://github.com/user-attachments/assets/974de49d-3999-452f-a5ae-fa077c544982)
![image](https://github.com/user-attachments/assets/3971a61b-8bca-4339-b141-db9a082f7fca)


## Known Issues and are planned for a fix in the future updates

- The Level creation doesnt work with Landscape maps as the landscape doesnt get duplicated


**Full Changelog**: https://github.com/shahilsaha05uk/Quick-Prototype-Plugin/commits/prototype

Please leave a feedback and tell us how we can improve

Happy Developing!!
