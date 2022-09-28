import pandas as pd


def get_data(path):
    return pd.read_csv(path)


def do_feature_scailing(
    data: pd.DataFrame, 
    feature: str
):
    assert feature in data.columns
    assert data[feature].dtype in ['float32', 'int64', 'float64']
    x = data[feature]
    m = data[feature].mean()
    std = data[feature].std()
    data[feature] = (x - m) / std


def data_pipeline(
    path: str = './data.csv',
    feature_1_colname = 'x1_kernel_area',
    feature_2_colname = 'x2_kernel_length',
    label_colname = 'wheat_varieties'
):
    data = get_data(path)
    do_feature_scailing(data, feature_1_colname)
    do_feature_scailing(data, feature_2_colname)
    print('===== Feature Scailing Result =====\n')
    print(data.head(), '\n')
    print(data.describe())
    print('\n==================================')
    return data


def main():
    data_pipeline()


if __name__ == '__main__':
    main()