import nltk
nltk.download('punkt')
from nltk.stem.lancaster import LancasterStemmer
stemmer = LancasterStemmer()

import numpy
import tflearn
import tensorflow
import random
import json
import pickle

with open("intents.json") as file:
        data = json.load(file)
try:
        with open("data.pickle", "rb") as f: #rb means read byte
                words, labels, training, output = pickle.laod(f) #save the 4 variables into pickle file
except:
        words = []
        labels = []
        docs_x = []
        docs_y = []

        #pre-processing of data
        for intent in data["intents"]:
             for pattern in intent["patterns"]:
                     wrds = nltk.word_tokenize(pattern)
                     words.extend(wrds)
                     docs_x.append(wrds)
                     docs_y.append(intent["tag"])

             if intent["tag"] not in labels:
                     labels.append(intent["tag"])


        words = [stemmer.stem(w.lower())for w in words if w != "?"]
        words = sorted(list(set(words)))
        labels = sorted(labels)

        training = []
        output = []

        out_empty = [0 for _ in range(len(labels))] #make it "1"," if kena one of the words , regardless of how many times

        for x, doc in enumerate(docs_x):
                bag = []

                wrds = [stemmer.stem(w) for w in doc] #every words looping thru

                for w in words:
                        if w in wrds:
                                bag.append(1)
                        else:
                                bag.append(0)

                output_row = out_empty[:]
                output_row[labels.index(docs_y[x])] = 1 #look through the label[] and see where the tag is, in the list and set the value to 1

                training.append(bag)
                output.append(output_row)

        training = numpy.array(training)
        output = numpy.array(output)

        with open("data.pickle", "wb") as f:
                pickle.dump((words, labels, training, output),f)

#model used for prediction of text
tensorflow.compat.v1.reset_default_graph()
net = tflearn.input_data(shape=[None, len(training[0])]) #each training input is same length, exp 45
net = tflearn.fully_connected(net, 8) #add this fully connected layer to neural network, which start at ^ input data
net = tflearn.fully_connected(net, 8)
net = tflearn.fully_connected(net, len(output[0]), activation="softmax") #get probability for each output
net = tflearn.regression(net)

#train model
model = tflearn.DNN(net)

#essentially is classifying one to a output

try:
        model.load("model.tflearn")
except:
        model.fit(training, output, n_epoch=1000, batch_size=8, show_metric=True) #no. epoch is the amount of time it sees, the more time the better it classifies
        model.save("model.tflearn")


#Predicting data using this model
def bag_of_words(s, words): #will take in list of words to create the bag of words
        bag = [0 for _ in range(len(words))] #create emtpy array
        s_words = nltk.word_tokenize(s)
        s_words = [stemmer.stem(word.lower())for word in s_words]

        #generate the bag of words
        for se in s_words:
                for i, w in enumerate(words):
                        if w == se:
                                bag[i]=(1)
        return numpy.array(bag)

#response to user
def chat():
        print("Start talking with the bot(type quit to stop!")
        while True:
                inp = input("You: ")
                if inp.lower() == "quit":
                        break

                results = model.predict([bag_of_words(inp, words)]) #throw into the function
                results_index = numpy.argmax(results)
                tag = labels[results_index]

                if results[results_index]>0.7:
                        for tg in data["intents"]:
                            if tg['tag'] == tag:
                                responses = tg['responses']
                        print(random.choice(responses))
                else:
                        print("I din't get that, try again.")

chat()