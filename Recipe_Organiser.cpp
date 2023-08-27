#include <iostream>
#include <vector>
#include <fstream>
#include <string>

// ... (Recipe struct, displayMainMenu, viewRecipes, and addRecipe functions) 
// Define a structure to represent a recipe
struct Recipe {
    std::string name;
    std::vector<std::string> ingredients;
    std::string instructions;
};

// Function to display the main menu options
void displayMainMenu() {
    std::cout << "Recipe Organizer / Cookbook" << std::endl;
    std::cout << "1. View Recipes" << std::endl;
    std::cout << "2. Add Recipe" << std::endl;
    std::cout << "3. Exit" << std::endl;
    std::cout << "Select an option: ";
}

// Function to view existing recipes
void viewRecipes(const std::vector<Recipe>& recipes) {
    std::cout << "=== Recipes ===" << std::endl;
    for (size_t i = 0; i < recipes.size(); ++i) {
        std::cout << i + 1 << ". " << recipes[i].name << std::endl;
    }
}

// Function to add a new recipe
void addRecipe(std::vector<Recipe>& recipes) {
    Recipe newRecipe;
    std::cout << "Enter recipe name: ";
    std::cin.ignore(); // Clear the newline character from the buffer
    std::getline(std::cin, newRecipe.name);

    std::cout << "Enter ingredients (one per line, type 'done' to finish):\n";
    while (true) {
        std::string ingredient;
        std::getline(std::cin, ingredient);
        if (ingredient == "done") {
            break;
        }
        newRecipe.ingredients.push_back(ingredient);
    }

    std::cout << "Enter instructions (type 'done' when finished):\n";
    while (true) {
        std::string instruction;
        std::getline(std::cin, instruction);
        if (instruction == "done") {
            break;
        }
        newRecipe.instructions += instruction + "\n";
    }

    recipes.push_back(newRecipe);
    std::cout << "Recipe added successfully!" << std::endl;
}

// Function to save recipes to a file
void saveRecipesToFile(const std::vector<Recipe>& recipes, const std::string& filename) {
    std::ofstream outFile(filename);
    
    if (outFile.is_open()) {
        for (const Recipe& recipe : recipes) {
            outFile << "Name: " << recipe.name << "\n";
            outFile << "Ingredients:\n";
            for (const std::string& ingredient : recipe.ingredients) {
                outFile << "- " << ingredient << "\n";
            }
            outFile << "Instructions:\n" << recipe.instructions << "\n";
            outFile << "\n"; // Add a separator between recipes
        }

        std::cout << "Recipes saved to " << filename << std::endl;
    } else {
        std::cerr << "Error: Unable to open file for writing." << std::endl;
    }
}

// Function to load recipes from a file
void loadRecipesFromFile(std::vector<Recipe>& recipes, const std::string& filename){
    std::ifstream inFile(filename);

    if (inFile.is_open()) {
        recipes.clear(); // Clear existing recipes before loading

        std::string line;
        Recipe currentRecipe;
        while (std::getline(inFile, line)) {
            if (line.find("Name: ") ==0){
                currentRecipe.name = line.substr(6);
            } else if (line == "Ingredients:"){
                currentRecipe.ingredients.clear();
                while (std::getline(inFile, line) && !line.empty()){
                    currentRecipe.ingredients.push_back(line.substr(2));
                }
            } else if (line == "Instructions:") {
                currentRecipe.instructions.clear();
                while (std::getline(inFile, line) && !line.empty()){
                    currentRecipe.instructions += line + "\n";
                }
                recipes.push_back(currentRecipe);
            }
        }

        std::cout << "Recipes loaded from" << filename << std::endl;
    } else {
        std::cerr << "Error: Unable to open file for reading." << std::endl;
    }
}


int main() {
    std::vector<Recipe> recipes;

    const std::string filename = "recipes.txt"; // Change this to your desired filename

    // Load existing recipes from the file at program start
    loadRecipesFromFile(recipes, filename);

    while (true) {
        displayMainMenu();

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                viewRecipes(recipes);
                break;
            case 2:
                addRecipe(recipes);
                break;
            case 3:
                saveRecipesToFile(recipes, filename);
                std::cout << "Exiting. Have a delicious day!" << std::endl;
                return 0;
            default:
                std::cout << "Invalid choice. Please select a valid option." << std::endl;
        }
    }

    return 0;
}
