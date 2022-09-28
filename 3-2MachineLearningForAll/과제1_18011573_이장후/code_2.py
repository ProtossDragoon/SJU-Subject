import code_1 as data_processing
from sklearn.model_selection import train_test_split 
from sklearn.linear_model import LogisticRegression


def get_xy(
    data, 
    feature_colnames: list, 
    label_colname: str, 
    split: bool = False
):
    x = data[feature_colnames]
    y = data[label_colname]
    if split:
        x_train, x_test, y_train, y_test = train_test_split(x, y)
        return x_train, x_test, y_train, y_test
    return x, y


def get_model(
    x_train,
    y_train,
):
    model = LogisticRegression(multi_class='ovr')
    model.fit(x_train, y_train)
    return model


def model_training_pipeline(
    data,
    feature_1_colname: str = 'x1_kernel_area',
    feature_2_colname: str = 'x2_kernel_length',
    label_colname: str = 'wheat_varieties'
):
    features = [feature_1_colname, feature_2_colname]
    x, y = get_xy(data, features, label_colname)
    model = get_model(x, y)
    return model
    
    
def main():
    data = data_processing.data_pipeline()
    model = model_training_pipeline(data)
    
    
if __name__ == '__main__':
    main()