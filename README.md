# FPSD-project

---

# Food Delivery App

## Table of Contents
1. [Introduction](#introduction)
2. [Features](#features)
3. [Directory Structure](#directory-structure)
4. [Setup and Installation](#setup-and-installation)
5. [Usage](#usage)
6. [Modules](#modules)
    - [Add to Cart](#add-to-cart)
    - [Animation](#animation)
    - [Cricket Game](#cricket-game)
    - [Collaborative Filter](#collaborative-filter)
    - [Delivery Boy Selection](#delivery-boy-selection)
    - [Favourites](#favourites)
    - [Food Items](#food-items)
    - [Food Order Page](#food-order-page)
    - [History](#history)
    - [Illustrations](#illustrations)
    - [Login](#login)
    - [Map](#map)
    - [Notifications](#notifications)
    - [Payment](#payment)
    - [Sounds](#sounds)
    - [Restaurants Home](#restaurants-home)
    - [Settings](#settings)
    - [Snake Games](#snake-games)
    - [Statistics](#statistics)
    - [Chat App](#chat-app)

## Introduction
This Food Delivery App is a comprehensive system that allows users to browse various food items, add them to the cart, and place orders. It also includes additional features like user reviews, collaborative filtering for personalized recommendations, delivery boy selection, interactive animations and games, a statistics module for tracking purchases, and a chat app for community interaction.

## Features
- User Authentication (Login and Registration)
- Browse and Search Food Items
- Add Food Items to Cart
- Place Orders
- View Order History
- Collaborative Filtering for Food Recommendations
- Delivery Boy Selection
- User and Delivery Partner Profiles
- Interactive Animations and Games
- Payment Processing
- Notifications
- Purchase Statistics
- Community Chat

## Directory Structure
```
food_delivery_app/
├── src/
│   ├── add_to_cart.c
│   ├── animation.c
│   ├── cricket_game.c
│   ├── collaborative_filter.c
│   ├── delivery_boy_selection.c
│   ├── favourites.c
│   ├── food_items.c
│   ├── food_order_page.c
│   ├── history.c
│   ├── illustrations.c
│   ├── login.c
│   ├── map.c
│   ├── notifications.c
│   ├── payment.c
│   ├── sounds.c
│   ├── restaurants_home.c
│   ├── settings.c
│   ├── snake_games.c
│   ├── statistics.c
│   ├── chat_app.c
│   ├── main.c
│   └── utils.c
├── include/
│   ├── add_to_cart.h
│   ├── animation.h
│   ├── cricket_game.h
│   ├── collaborative_filter.h
│   ├── delivery_boy_selection.h
│   ├── favourites.h
│   ├── food_items.h
│   ├── food_order_page.h
│   ├── history.h
│   ├── illustrations.h
│   ├── login.h
│   ├── map.h
│   ├── notifications.h
│   ├── payment.h
│   ├── sounds.h
│   ├── restaurants_home.h
│   ├── settings.h
│   ├── snake_games.h
│   ├── statistics.h
│   ├── chat_app.h
│   └── utils.h
├── data/
│   ├── food_items.txt
│   ├── users.txt
│   ├── orders.txt
│   ├── ratings.txt
│   ├── purchases.txt
│   ├── messages.txt
├── README.md
├── Makefile
```

## Setup and Installation
1. **Clone the repository:**
   ```bash
   git clone https://github.com/Itz-mehanth/FSDC-project.git
   cd food_delivery_app
   ```
2. **Run the application:**
   ```bash
   ./output
   ```

## Usage
1. Launch the application using the command mentioned above.
2. Navigate through the menu to register or login.
3. Browse food items, add them to the cart, and place orders.
4. Use the side menu to access different features like viewing order history, checking notifications, playing games, viewing purchase statistics, and engaging in the community chat.

## Modules

### Add to Cart
Handles the functionality of adding food items to the user's cart.

### Animation
Contains functions for displaying interactive animations.

### Cricket Game
Module for a cricket game that users can play while waiting for their order.

### Collaborative Filter
Provides personalized food recommendations based on user ratings.

### Delivery Boy Selection
Manages the selection and assignment of delivery boys for orders.

### Favourites
Allows users to view and manage their favourite food items.

### Food Items
Manages the food items available in the menu, including loading from file and displaying.

### Food Order Page
Handles the ordering process, including displaying the cart and placing orders.

### History
Displays the order history for the user.

### Illustrations
Contains functions for displaying various illustrations and animations.

### Login
Manages user authentication, including login and registration.

### Map
Provides mapping functionalities for finding nearby restaurants and delivery locations.

### Notifications
Handles notifications for users about order status and other updates.

### Payment
Manages the payment process for orders, including simulation of different payment methods.

### Sounds
Contains functions for playing various sounds throughout the application.

### Restaurants Home
Manages the display and selection of restaurants.

### Settings
Allows users to change settings like delivery address and preferences.

### Snake Games
Includes a snake game for users to play.

### Statistics
Manages and displays statistics related to user purchases.

### Chat App
Handles community chat functionality, allowing users to read and send messages.

## Statistics
The statistics module includes functionalities for reading purchase data, summarizing daily totals, and visualizing statistics. It provides:
- Reading and parsing purchase entries.
- Summarizing daily purchase amounts.
- Finding minimum and maximum purchase amounts.
- Normalizing data for visualization.
- Printing bar charts for daily summaries.

## Chat App
The chat app module enables users to participate in community chat. It provides:
- Reading messages from a file.
- Writing messages to a file.
- Displaying chat messages with user details and timestamps.
- Calculating and displaying elapsed time since messages were sent.
- Interactive chat interface using `windows.h` for enhanced user interaction.

## Interactive Features
The app uses `windows.h` to create interactive elements such as buttons and popups, enhancing the user experience with a more responsive and engaging interface.


## Contributing
1. Fork the repository.
2. Create a new branch (`git checkout -b feature-branch`).
3. Commit your changes (`git commit -am 'Add new feature'`).
4. Push to the branch (`git push origin feature-branch`).
5. Create a new Pull Request.

## Contact
For any questions or feedback, please contact [mehanth362@gmail.com](mailto:mehanth362@gmail.com).

---

