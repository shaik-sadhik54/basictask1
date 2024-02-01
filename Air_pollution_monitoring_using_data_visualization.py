import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import datetime 
import matplotlib.dates as md
df=pd.read_csv('deccanpollution.csv')
df.head()
df.drop("entry_id",axis=1,inplace=True)
df.head()
#finding out the time when max pollution at mumbai
df[df['Mumbai']==1.979964835].drop(['Hyderabad','Chennai'],axis=1)
 #finding out the time when max pollution at hydrabad
df[df['Hyderabad']==2.869090842].drop(['Mumbai','Chennai'],axis=1)
 #finding out the time when max pollution at chennai
df[df['Chennai']==2.705852381].drop(['Mumbai','Hyderabad'],axis=1)
#finding out pollution level at Mumbai by hourly update
plt.figure(figsize=(12,8))
plt.rcParams.update({'font.size':12})
x =pd.to_datetime(df['created_at'])
y=df['Mumbai']
plt.plot_date(x, y,color='blue')
plt.xlabel("Data & Hour")
plt.ylabel("Pollution Level")
plt.title("Hourly Pollution Level at Mumbai")
#finding out pollution level at Hyderabad by hourly update
plt.figure(figsize=(12,8))
plt.rcParams.update({'font.size':12})
x =pd.to_datetime(df['created_at'])
y=df['Hyderabad']
plt.plot_date(x, y,color='green')
plt.xlabel("Data & Hour")
plt.ylabel("Pollution Level")
plt.title("Hourly Pollution Level at Hyderabad")
#finding out pollution level at chennai by hourly update
plt.figure(figsize=(12,8))
plt.rcParams.update({'font.size':12})
x =pd.to_datetime(df['created_at'])
y=df['Hyderabad']
plt.plot_date(x, y,color='red')
plt.xlabel("Data & Hour")
plt.ylabel("Pollution Level")
plt.title("Hourly Pollution Level at Chennai ")
import warnings
warnings.filterwarnings("ignore", message="The figure layout has changed to tight")
#pairplotting
sns.set(font_scale=1.5)
g=sns.pairplot(df,hue="Mumbai")
g.fig.set_size_inches(10,10)
sns.jointplot(x="Mumbai",y="Hyderabad",data=df,color='blue')
sns.jointplot(x="Mumbai",y="Chennai",data=df,color='green')
sns.jointplot(x="Chennai",y="Hyderabad",data=df,color='red')