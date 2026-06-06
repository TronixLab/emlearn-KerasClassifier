# emlearn-KerasClassifier

Deploy a Keras crop recommendation model to a microcontroller with the
[emlearn](https://github.com/emlearn/emlearn) TinyML framework.

## Overview

This repository shows an end-to-end workflow for:

- training a crop recommendation classifier in Keras
- converting the trained model for embedded use with emlearn
- running inference from an Arduino sketch

The example predicts one of 22 crop classes from 7 input features and includes
the generated model headers used by the Arduino project.

## Repository contents

- `CropsRecommendation_Classification.ipynb` - notebook used to train and export the model
- `CropsRecommendation_Classification.html` - exported notebook report
- `crop_recommendation.csv` - dataset used for training
- `emlearn_Arduino_Keras_CropReco/` - Arduino sketch and generated headers for inference

## Install emlearn

Install the Python package:

```bash
pip install emlearn
```

## Install the Arduino emlearn library

After installing the Python package, install the emlearn Arduino library into
your Arduino libraries folder with:

```bash
python -m emlearn.arduino.install
```

This command copies the emlearn Arduino support files into your local Arduino
library directory so the sketch can include `eml_net.h`.

## Use this project

1. Open `CropsRecommendation_Classification.ipynb` to review the training and model export flow.
2. Ensure emlearn is installed with `pip install emlearn`.
3. Run `python -m emlearn.arduino.install` to install the Arduino emlearn library.
4. Open `emlearn_Arduino_Keras_CropReco/emlearn_Arduino_Keras_CropReco.ino` in the Arduino IDE.
5. Build and upload the sketch to a supported board.
6. Send comma-separated feature values over Serial to receive the predicted crop class and probability.
