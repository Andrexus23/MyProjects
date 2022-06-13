import pickle

alarms = []
file = 'D:\\work\\alarms.pkl'
with open(file, 'wb') as f:
    try:
        pickle.dump(alarms, f)
    except pickle.PicklingError:
        print('Error while reading from object. Object is not pickable')
