# Mini-ShoppingAndBilling-System-using-DataStructures-in-C
The code creates a mini shopping and billing system which can be used for billing of items purchased by a customer and updation as well as checking of the stock by the manager.
The cart in the code used by the customers involve the use of linked list data structure because of its dynamic nature. Thus adding an item and deleting an item is quick and easy process.
The stock management utilizes binary tree data structure. The stock is divided into sub classes i.e. electronics, foot items and stationary with each one having its own binary tree. The head pointer of all the 3 binary trees are stored in an array. This is done so that the code can be made scalable to more sub classes of items as well.
The bill is available in the same folder after the user gives the permission to print the bill.
Electronics.war, FoodItems.war and Stationary.war contains the data of the products available in the store. These cannot be altered outside the shopping system due to the .war extension.
