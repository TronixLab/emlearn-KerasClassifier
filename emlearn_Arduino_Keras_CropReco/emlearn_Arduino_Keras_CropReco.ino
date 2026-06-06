#include "NeuralNetworkClassifier.h"
#include "MinMaxScaler.h"

// Create scaler instance
MinMaxScaler scaler;

// Array to hold scaled features
float features_scaled[MinMaxScaler::n_features];

// Define an array for class labels
const char* classes[] = { "apple", "banana", "blackgram", "chickpea", "coconut",
                          "coffee", "cotton", "grapes", "jute", "kidneybeans",
                          "lentil", "maize", "mango", "mothbeans", "mungbean",
                          "muskmelon", "orange", "papaya", "pigeonpeas", "pomegranate",
                          "rice", "watermelon" };

// Array to hold prediction probabilities
float proba[MinMaxScaler::n_features];

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    String line = Serial.readStringUntil('\n');
    float features[MinMaxScaler::n_features];
    int featureIndex = 0;
    int lastIndex = 0;
    line.trim();

    while (featureIndex < MinMaxScaler::n_features) {
      int commaIndex = line.indexOf(',', lastIndex);
      String value;
      if (commaIndex == -1) {
        value = line.substring(lastIndex);
      } else {
        value = line.substring(lastIndex, commaIndex);
      }
      features[featureIndex] = value.toFloat();
      featureIndex++;
      if (commaIndex == -1) break;
      lastIndex = commaIndex + 1;
    }

    // Scale features
    scaler.transform(features, features_scaled);

    // Make prediction
    int32_t y_pred = NeuralNetworkClassifier_predict(features_scaled, MinMaxScaler::n_features);

    // Get prediction probabilities
    EmlError err = eml_net_predict_proba(&NeuralNetworkClassifier, features_scaled, MinMaxScaler::n_features, proba, 22);
    if (err == EmlOk) {
      // Print prediction probability
      Serial.print("Predicted Class: ");
      Serial.print(classes[y_pred]);
      Serial.print("\t Probability: ");
      Serial.print(proba[y_pred] * 100, 2);
      Serial.println("%");
    }
  }
  delay(100);
}