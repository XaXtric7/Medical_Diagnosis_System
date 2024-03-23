#ifndef DIAGNOSISWIDGET_H
#define DIAGNOSISWIDGET_H
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QFormLayout>
#include <QMessageBox>
#include <QTextEdit>

class DiagnosisWidget : public QWidget {
    Q_OBJECT

public:
    explicit DiagnosisWidget(QWidget *parent = nullptr);

private slots:
    void provideDiagnosis();

private:

    QLineEdit nameLineEdit;
    QLineEdit ageLineEdit;
    QLineEdit symptomsLineEdit;
    QLineEdit temperatureLineEdit;
    QTextEdit *diagnosisTextEdit;
};

#endif // DIAGNOSISWIDGET_H
