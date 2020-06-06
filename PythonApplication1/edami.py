import csv

from spade import frequent_patterns_search

#Your data needs to be in a particular format similar to the following:

# 1 1 3 8 37 42
# 1 2 4 4 11 37 42
# 2 1 2 10 73
# 2 2 1 72
# 2 3 3 4 24 77 

# where numbers are:
# sequence id, event id, number of items, items

def prepare_dress_sales_dataset():
    with open('../data/processed_dress_sales', 'a') as processed_file:
        with open('../data/dress_sales.csv', 'r') as csv_file:
            csv_reader = csv.reader(csv_file, delimiter=';')
            dates = []
            line_count = 0
            for row in csv_reader:
                if line_count == 0:
                    dates = row[1:24]
                    line_count += 1
                else:
                    item_id = row[0]
                    item_sales_records = row[1:24]
                    for i in range(len(dates)):
                        processed_file.write(item_id + ' ' + dates[i] + ' 1 ' + item_sales_records[i] + '\n')




if __name__ == "__main__":
    prepare_dress_sales_dataset()
    frequent_patterns_search('../data/processed_dress_sales', 0.6)
