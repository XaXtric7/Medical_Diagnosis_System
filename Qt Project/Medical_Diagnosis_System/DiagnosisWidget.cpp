// DiagnosisWidget.cpp

#include "DiagnosisWidget.h"
#include <QPalette>
#include <QFont>
#include <QPixmap>
#include <QIcon>
#include <QPushButton>
#include <QToolTip>
#include <QMessageBox>

DiagnosisWidget::DiagnosisWidget(QWidget *parent) : QWidget(parent) {
    // Set window title
    setWindowTitle("Medical Diagnosis Application");
    resize(800, 700);

    // Set the background color to black
    QPalette pal = palette();
    pal.setColor(QPalette::Window, Qt::black);
    setAutoFillBackground(true);
    setPalette(pal);

    // Create a vertical layout to arrange widgets
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Display welcome message
    QLabel *welcomeLabel = new QLabel("Hello, welcome to the Medical Diagnosis System!", this);
    welcomeLabel->setStyleSheet("color: #66CDAA; font-size: 18px;");
    welcomeLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(welcomeLabel);

    // Adding logo to the application
    QPixmap logoPixmap("C:/Users/sarth/OneDrive/Pictures/Screenshots/qt1.PNG"); // Load the logo from resources
    QLabel *logoLabel = new QLabel(this);
    logoLabel->setPixmap(logoPixmap.scaled(200, 200, Qt::KeepAspectRatio)); // Scale the logo
    logoLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(logoLabel);

    // Create form layout for input fields
    QFormLayout *formLayout = new QFormLayout;
    mainLayout->addLayout(formLayout);

    // Set the font color to white
    QPalette textPalette = palette();
    textPalette.setColor(QPalette::Text, Qt::white);

    // Add row to the form layout
    QLabel *nameLabel = new QLabel("Patient Name:");
    nameLabel->setPalette(textPalette);
    formLayout->addRow(nameLabel, &nameLineEdit);

    QLabel *ageLabel = new QLabel("Patient Age:");
    ageLabel->setPalette(textPalette);
    formLayout->addRow(ageLabel, &ageLineEdit);

    QLabel *symptomsLabel = new QLabel("Symptoms:");
    symptomsLabel->setPalette(textPalette);
    formLayout->addRow(symptomsLabel, &symptomsLineEdit);

    QLabel *temperatureLabel = new QLabel("Temperature (F):");
    temperatureLabel->setPalette(textPalette);
    formLayout->addRow(temperatureLabel, &temperatureLineEdit);

    // Set custom font
    QFont font("Arial",12); // Set font family and size
    nameLabel->setFont(font);
    ageLabel->setFont(font);
    symptomsLabel->setFont(font);
    temperatureLabel->setFont(font);

    diagnosisTextEdit = new QTextEdit;
    diagnosisTextEdit->setReadOnly(true);
    diagnosisTextEdit->setFont(font);
    // Set the background color of the text box to light gray
    QPalette textBoxPalette = diagnosisTextEdit->palette();
    textBoxPalette.setColor(QPalette::Base, QColorConstants::Black);
    textBoxPalette.setColor(QPalette::Text, Qt::green); // Text color
    diagnosisTextEdit->setPalette(textBoxPalette);

    formLayout->addRow(new QLabel("Diagnosis Result:"), diagnosisTextEdit);

    // Set label color to grey
    QPalette labelPalette = palette();
    labelPalette.setColor(QPalette::WindowText, Qt::green);
    nameLabel->setPalette(labelPalette);
    ageLabel->setPalette(labelPalette);
    symptomsLabel->setPalette(labelPalette);
    temperatureLabel->setPalette(labelPalette);

    // Connect the editingFinished signal to the provideDiagnosis slot
    connect(&temperatureLineEdit, &QLineEdit::editingFinished, this, &DiagnosisWidget::provideDiagnosis);
    connect(&ageLineEdit, &QLineEdit::editingFinished, this, &DiagnosisWidget::provideDiagnosis);

    // Add Submit Button
    QPushButton *submitButton = new QPushButton("Submit", this);
    submitButton->setStyleSheet("background-color: #66CDAA; color: white; border: none; padding: 10px 20px; font-size: 16px;");
    submitButton->setToolTip("Click to submit and get diagnosis");
    mainLayout->addWidget(submitButton);

    // Connect submitButton clicked signal to provideDiagnosis slot
    connect(submitButton, &QPushButton::clicked, this, &DiagnosisWidget::provideDiagnosis);

    // Add Exit Button
    QPushButton *exitButton = new QPushButton("Exit", this);
    exitButton->setStyleSheet("background-color: #FF6347; color: white; border: none; padding: 10px 20px; font-size: 16px;");
    exitButton->setToolTip("Click to exit the application");
    mainLayout->addWidget(exitButton);

    // Connect exitButton clicked signal to close the application
    connect(exitButton, &QPushButton::clicked, this, &QWidget::close);
}

void DiagnosisWidget::provideDiagnosis() {
    bool ok;
    double age = ageLineEdit.text().toDouble(&ok);
    double temperature = temperatureLineEdit.text().toDouble(&ok);
    if (ok && !temperatureLineEdit.text().isEmpty()) {
        QString diagnosis, remedies, treatment;
        if (temperature < 96  ) {
            diagnosis = "Hypothermia";
            treatment = "Take acetaminophen or ibuprofen \n drink fluids, take rest \n If it gets severe take medical attention ASAP";
        } else if (temperature >= 97 && temperature <= 99) {
            diagnosis = "Normal";
        } else if (temperature > 99 && temperature <= 101) {
            diagnosis = "Fever";
        } else {
            diagnosis = "High fever";
        }
        diagnosisTextEdit->setText("Diagnosis based on temperature: \n" + diagnosis +"\n"+treatment);
    } else {
        // Invalid input, show error message
        QMessageBox::critical(this, "Error", "Invalid input! Please enter a valid temperature.", QMessageBox::Ok);
    }
}
