#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <limits>

using namespace std;

// Function prototypes
void displaySymptomsMenu();
void displayInputPrompt(const string &prompt);
void clearInputBuffer();
void displayHeader(const string &text);
void displayErrorMessage(const string &message);
void displayRemedy(const string &disease, const pair<string, string> &remedy);
int choice;

// Function to suggest a remedy based on the guessed disease
map<string, pair<string, string>> suggestRemedy(const vector<string> &diseases, int age);

// Function to guess the disease based on symptoms, temperature, height, and age
vector<string> guessDisease(const vector<string> &symptoms, double temperature, double height, int age);

int main()
{
    // Input patient information
    string name;
    int age;
    char gender;
    double temperature;
    double height;

    cout << "\n\t--- Welcome to the Medical Diagnosis System ---\n\n";

    // Get patient's name
    displayInputPrompt("Enter patient's name: ");
    getline(cin, name);

    // Get patient's age
    displayInputPrompt("Enter patient's age: ");
    while (!(cin >> age) || age <= 0)
    {
        displayErrorMessage("Invalid input. Please enter a valid age.");
        clearInputBuffer();
    }

    // Get patient's gender
    displayInputPrompt("Enter the gender (M/F): ");
    while (!(cin >> gender) || (gender != 'M' && gender != 'F'))
    {
        displayErrorMessage("Invalid input. Please enter 'M' or 'F'.");
        clearInputBuffer();
    }

    // Get patient's body temperature
    displayInputPrompt("Enter patient's body temperature (in Fahrenheit): ");
    while (!(cin >> temperature))
    {
        displayErrorMessage("Invalid input. Please enter a valid temperature.");
        clearInputBuffer();
    }

    // Get patient's height
    displayInputPrompt("Enter patient's height (in centimeters): ");
    while (!(cin >> height) || height <= 0)
    {
        displayErrorMessage("Invalid input. Please enter a valid height.");
        clearInputBuffer();
    }

    // Input symptoms from the user
    vector<string> symptoms;
    char moreSymptoms;
    displaySymptomsMenu();
    do
    {
        string symptom;
        displayInputPrompt("\nEnter symptom: ");
        cin >> symptom;
        symptoms.push_back(symptom);
        cout << "Add more symptoms? (Y/N): ";
        cin >> moreSymptoms;
    } while (moreSymptoms == 'Y' || moreSymptoms == 'y');

    // Guess the diseases based on symptoms, temperature, height, and age
    vector<string> guessedDiseases = guessDisease(symptoms, temperature, height, age);

    // Suggest remedies based on the guessed diseases
    map<string, pair<string, string>> remedies = suggestRemedy(guessedDiseases, age);

    // Output diagnosis and remedies
    for (const auto &disease : guessedDiseases)
    {
        displayHeader("Diagnosis for " + name + ": " + disease);
        displayRemedy(disease, remedies[disease]);
    }

    cout << "\n\t--- Thank you for using the Medical Diagnosis System ---\n\n";

    return 0;
}

void displaySymptomsMenu()
{
    cout << "=== Enter Symptoms ===\n";
    cout << "Please enter the symptoms one by one. Type 'done' when finished.\n";
}

void displayInputPrompt(const string &prompt)
{
    cout << prompt;
}

void clearInputBuffer()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void displayHeader(const string &text)
{
    cout << "\n--- " << text << " ---\n\n";
}

void displayErrorMessage(const string &message)
{
    cout << "Error: " << message << endl;
}

void displayRemedy(const string &disease, const pair<string, string> &remedy)
{
    cout << "Suggested remedy: " << remedy.first << endl;
    cout << "Medicine: " << remedy.second << endl;
}

map<string, pair<string, string>> suggestRemedy(const vector<string> &diseases, int age)
{
    // Your implementation of suggestRemedy function
    // This is just a placeholder for demonstration
    map<string, pair<string, string>> remedies = {
        {"Mild cold", {"Take Rest, drink a lot of fluids, Run a cool-mist humidifier", age <= 10 ? "Cold syrup,Use nasal saline,\nJustkof D Junior Composition: Dextromethorphan + Phenylephrine 5mg + CPM 2mg" : "High power cold tablets,\nPEACEMOL-D Tablets Composition: Paracetamol & Domperidone Tablets\nASTADIN Tablets Composition: Loratadine Tablets"}},
        {"Severe fever", {"Take acetaminophen or ibuprofen, drink fluids, take rest, if it gets severe take medical attention ASAP", age < 10 ? "Fever syrup\n(Tylenol, others), if your child is age 6 months or older, ibuprofen (Advil, Motrin, others) is OK, too." : "High power fever tablets\ntake acetaminophen (Tylenol, others), ibuprofen (Advil, Motrin IB, others) or aspirin.\nRead the label carefully for proper dosage, and be careful not to take more than one medication containing acetaminophen, such as some cough and cold medicines"}},
        {"Headache", {"Take pain relievers such as ibuprofen or acetaminophen, \nRest in a quiet, dark room,\n(1)Drink water,\n(2)Limit alcohol,\n(3)Try essential oils", age < 10 ? "Pain relief syrup,or intake of \n(1)Riboflavin, \n(2)Magnesium, \n(3)Coenzyme Q10, \n(4)Vitamin D" : "High power pain relief tablets like, \n(1)Acetaminophen, \n(2)Aspirin, \n(3)Fenoprofen"}},
        {"Stomachache", {"Avoid spicy or fatty foods, drink herbal tea, take antacids if necessary, Lemon water, Intake of Ginger in tea, cinnamon, cumin, banana can give relief", age < 10 ? "Stomachache syrup, \nRubbing a child’s tummy or having a distraction, such as reading a book, can sometimes ease the pain.\nGive paracetamol or ibuprofen if your child is in pain or is miserable.\nIf ibuprofen causes a stomach upset, offer your child some food or milk." : "High power stomachache tablets like, \n(1)Aztreonam, \n(2)Bismuth Subsalicylate, \n(3)Budesonide etc\n if pain becomes severe please refer to your nearest doctor"}},
        // Add more diseases and remedies as needed
    };

    map<string, pair<string, string>> suggestedRemedies;
    for (const string &disease : diseases)
    {
        auto it = remedies.find(disease);
        if (it != remedies.end())
        {
            suggestedRemedies[disease] = it->second;
        }
    }

    return suggestedRemedies;
}

vector<string> guessDisease(const vector<string> &symptoms, double temperature, double height, int age)
{
    // Your implementation of guessDisease function
    // This is just a placeholder for demonstration
    vector<string> guessedDiseases;
    bool hasFever = false;

    for (const string &symptom : symptoms)
    {
        if (symptom == "Headache" || symptom == "headache")
        {
            guessedDiseases.push_back("Headache");
        }
        else if (symptom == "Stomachache" || symptom == "stomachache")
        {
            guessedDiseases.push_back("Stomachache");
        }
    }
    if (temperature > 99 && temperature <= 100)
    {
        guessedDiseases.push_back("Mild cold");
        hasFever = true;
    }
    else if (temperature > 100)
    {
        guessedDiseases.push_back("Severe fever");
        hasFever = true;
    }
    if (!hasFever)
    {
        cout << "\nIt seems you don't have a cold or a fever" << endl;
        cout << "We are glad to know that you are healthy " << endl;
        cout << "Here are some suggestions for you to avoid unnecessary illness" << endl;
        cout << "(1)Maintain Good Hygiene,\n(2)Eat a Balanced Diet,\n(3)Stay Hydrated,\n(4)Get Regular Exercise,\n(5)Get Adequate Sleep";
    }

    return guessedDiseases;
}
