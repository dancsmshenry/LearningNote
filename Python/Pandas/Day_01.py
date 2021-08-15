import pandas as pd
import pymysql
import numpy as np

'''
Pandas读取数据
'''
# 读取csv数据
fpath = "./datas/ml-latest-small/ratings.csv"  # 前面一定要加上./
ratings = pd.read_csv(fpath)
# print(ratings.head())查看前几行数据
# print(ratings.shape)查看数据的形状
# print(ratings.columns)查看列名列表
# print(ratings.dtypes)查看每一列数据的类型
print(ratings.index)  # RangeIndex(start=0, stop=100836, step=1)不太明

# 读取txt数据
fpath = "./datas/crazyant/access_pvuv.txt"
pvuv = pd.read_csv(fpath, sep="\t", header=None, names=['pdate', 'pv', 'uv'])
# print(pvuv)查看txt数据

# 读取excel文件
# 这里出现了问题，一开始说是要安装xlrd库，后面说xird库大于2.0以后，还有按爪给你openyxl才可以读取xls数据和xlsx数据
fpath = "./datas/crazyant/access_pvuv.xlsx"
pvuv = pd.read_excel(fpath)
# print(pvuv)

# 读取mysql数据库
'''
conn = pymysql.connect(host = "127.0.0.1",
        user='root',
        password='12345678',
        database='test',
        charset='utf8')
mysql_page = pd.read_sql("", con = conn)
print(mysql_page)
'''

'''
Pandas数据结构
'''
# Series
# 仅有数据列表即可产生最简单的Series
s1 = pd.Series([1, 2, 3, 4, 'a', 'b'])
# print(s1)左侧为索引，右侧是数据
print(s1.index)  # RangeIndex(start=0, stop=6, step=1)不太明
# print(s1.values)获取数据

# 创建一个具有标签索引的Series
s2 = pd.Series([1, 'a', 5.2, 7], index=['d', 'b', 'a', 'c'])  # index是索引
# print(s2)查询索引和数据
# print(s2.index)查询索引
# print(s2.values)查询数据
# print(s2['d'])根据索引返回数据
# print(s2['d':'a'])类似数组的用法

# 使用Python字典创建Series
sdata = {'Ohio': 35000, 'Texas': 72000, 'Oregon': 16000, 'Utah': 5000}
s3 = pd.Series(sdata)
# print(s3)查询索引和数据

# dataframe
# dataframe,每行每列都有索引，类似excel表格
data = {
    'state': ['Ohio', 'Ohio', 'Ohio', 'Nevada', 'Nevada'],
    'year': [2000, 2001, 2002, 2001, 2002],
    'pop': [1.5, 1.7, 3.6, 2.4, 2.9]
}
df = pd.DataFrame(data)
# print(df)
# print(df.dtypes)输出每一列的类型
# print(df.columns)输出索引以及类型
# print(df.index)RangeIndex(start=0, stop=5, step=1)

# dataframe的查询
# print(df['state'])查询一列的所有元素加上行的索引
# print(type(df['state']))查询类型 <class 'pandas.core.series.Series'>
# print(df[['year','state']]) 多条件查询列
# print(type(df[['year', 'pop']])) 查询类型 pandas.core.frame.DataFrame
# print(df.loc[1])查询一行
# print(df.loc[1:3])查询多行

'''
pandas查询数据
'''
df = pd.read_csv("../datas/beijing_tianqi/beijing_tianqi_2018.csv")

# 数据清洗
df.set_index('ymd', inplace=True)  # 将ymd作为新的索引，而不是数据的某一列
# replace是将数据中的某一项代替，astype是重新定义数据的类型
df.loc[:, "bWendu"] = df["bWendu"].str.replace("℃", "").astype('int32')
df.loc[:, "yWendu"] = df["yWendu"].str.replace("℃", "").astype('int32')
df.loc[:, "aqiInfo"] = df["aqiInfo"].str.replace("良", "良好").astype('string')
df.loc[:, "aqiInfo"] = df["aqiInfo"].str.replace("优", "优秀").astype('string')


# []左边是行，右边是列，

# 使用单个label值查询
# print(df.loc['2018-01-03', 'bWendu'])#前面是索引名，后面是要查询的列的数据
# print(df.loc['2018-01-03', ['bWendu', 'yWendu']])

# 使用值列表批量查询
# (df.loc[['2018-01-03','2018-01-04','2018-01-05'], 'bWendu'])#前面是多个索引，后面是要查的数据
# print(df.loc[['2018-01-03','2018-01-04','2018-01-05'], ['bWendu', 'yWendu']])

# 按照数值区间查询
# print(df.loc['2018-01-03':'2018-01-05', 'bWendu'])
# print(df.loc['2018-01-03', 'bWendu':'fengxiang'])
# print(df.loc['2018-01-03':'2018-01-05', 'bWendu':'fengxiang'])

# 条件查询
# print(df.loc[df["yWendu"] < -10, :])
# print(df.loc[(df["bWendu"]<=30) & (df["yWendu"]>=15) & (df["tianqi"]=='晴') & (df["aqiLevel"]==1), :])
# 复杂条件查询，中间用&隔开

# 函数查询
def query_my_data(df):
    return df.index.str.startswith("2018-09") & (df["aqiLevel"] == 1)


# print(df.loc[query_my_data, :])


'''
Pandas新增数据列
'''
# 直接添加
fpath = "./datas/beijing_tianqi/beijing_tianqi_2018.csv"
df = pd.read_csv(fpath)
print(df.head())
# 清洗数据
df.loc[:, "bWendu"] = df["bWendu"].str.replace("℃", "").astype('int32')
df.loc[:, "yWendu"] = df["yWendu"].str.replace("℃", "").astype('int32')
# 添加新的一列数据
df.loc[:, "wencha"] = df["bWendu"] - df["yWendu"]
df.loc[:, "zheshixindeyihang"] = 'XD'


# df.apply方法
def get_wendu_type(x):
    if x["bWendu"] > 33:
        return '高温'
    if x["yWendu"] < -10:
        return '低温'
    return '常温'
# 注意需要设置axis==1，这是series的index是columns
#df.loc[:, "wendu_type"] = df.apply(get_wendu_type, axis=1)
#print(df.head())


# df.assign(),返回的是一个新的副本，不会改变原来的数组
df1 = df.assign(yWendu_huashi=lambda x: x['yWendu'] * 9 / 5 + 32)


#按条件选择分组赋值
df['wendu_type'] = ''
df.loc[df["bWendu"] - df["yWendu"] > 10, "wencha_type"] = "温差大"
df.loc[df["bWendu"] - df["yWendu"] <= 10, "wencha_type"] = "温差小"
#print(df["wencha_type"].value_counts())
#value_counts()统计该列中每一项出现的次数


'''
Pandas数据排序
'''
fpath = "./datas/beijing_tianqi/beijing_tianqi_2018.csv"
df = pd.read_csv(fpath)

# 替换掉温度的后缀℃
df.loc[:, "bWendu"] = df["bWendu"].str.replace("℃", "").astype('int32')
df.loc[:, "yWendu"] = df["yWendu"].str.replace("℃", "").astype('int32')

#print(df["aqi"].sort_values())对这一列的数据排序并输出，左边是数据的索引，右边是数据，从小到大排序
#print(df["aqi"].sort_values(ascending=False))从大到小排序
#print(df.sort_values(by = "aqi"))也是从小到大，但会返回整个列表
#print(df.sort_values(by = "aqi", ascending=False))从大到小
#print(df.sort_values(by = ["aqiLevel", "bWendu"]))多项条件排序
#print(df.sort_values(by = ["aqiLevel", "bWendu"], ascending = False))多项条件排序
#print(df.sort_values(by = ["aqiLevel", "bWendu"], ascending = [False, True]))多项条件排序,左边降序，右边升序
#先看左边，再看右边


'''
Pandas字符串函数
'''
fpath = "./datas/beijing_tianqi/beijing_tianqi_2018.csv"
df = pd.read_csv(fpath)
print(df["bWendu"].str)#<pandas.core.strings.accessor.StringMethods object at 0x00000167F7F30100>
#字符串替换
df["bWendu"] = df["bWendu"].str.replace("℃", "")
#判断是不是数字
#print(df["bWendu"].str.isnumeric())
'''
0       True
1       True
2       True
3       True
4       True
       ...  
360    False
361    False
362    False
363    False
364    False
'''
#条件查询
condition = df["ymd"].str.startswith("2018-03")
print(df[condition].head())