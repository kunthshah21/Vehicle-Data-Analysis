"""
Created on Mon Apr  1 23:01:49 2024

@author: kunthshah
"""

import pandas as pd

def remove_null_rows(csv_file):
    # Read CSV file into a DataFrame
    df = pd.read_csv(csv_file)
    
    # Drop rows with any null values
    df.dropna(inplace=True)
    
    # Write the DataFrame back to a CSV file
    df.to_csv('cleaned_' + csv_file, index=False)
    
    print("Null rows removed and cleaned CSV file saved as 'cleaned_" + csv_file + "'")

# Replace 'your_file.csv' with the name of your CSV file
remove_null_rows('car_prices.csv')
