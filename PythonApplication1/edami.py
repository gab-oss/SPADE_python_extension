import csv
import os

from spade import frequent_patterns_search
from timeit import default_timer as timer

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


def process_generated_file(generated_file_name, new_file_name, seq_id = 1):
    '''
        Makes a new txt file, which contains transaction data generated by the IBM geneator in a different format.
        Generated files consist of row and each row containts a pair of numbers:
            transaction_no item_no
        which means that for every transaction there is as many rows starting with its number as there is items in it.
        
        To use frequent_patterns_search(filename) function, we need files in format:
        sequence_id event_id number_of_items item1 item2 item3...
        In the case of data from those generated files, transaction_no is used as event_id. 
        All events are considered to belong to one sequence with id as provided by the user.
    '''
    last_transaction_no = 0
    loaded_event = []
    with open(new_file_name, 'a') as processed_file:
        with open(generated_file_name, 'r') as generated_file:
            while True:
                line = generated_file.readline()
                if not line:
                    new_processed_line = ' '.join(loaded_event)
                    processed_file.write(new_processed_line)
                    break
                splitted_line = line.split()
                transaction_no = splitted_line[0]
                item_no = splitted_line[1]
                if transaction_no != last_transaction_no:
                    if loaded_event != []:
                        loaded_event.insert(2, str(len(loaded_event) - 2))
                        new_processed_line = ' '.join(loaded_event) + '\n'
                        processed_file.write(new_processed_line)
                    last_transaction_no = transaction_no
                    loaded_event = [str(seq_id), str(transaction_no), str(item_no)]
                else:
                    loaded_event.append(str(item_no))



def generated_files_as_sequences(generated_file_names, new_file_name, first_seq_id = 1):
    '''
        Processes a number of generated files into our format and combines their contents as a number of sequences.
    '''
    if os.path.exists(new_file_name):
        os.remove(new_file_name)
    seq_id = first_seq_id
    for filename in generated_file_names:
        process_generated_file(filename, new_file_name, seq_id)
        seq_id += 1


if __name__ == "__main__":
    data_dir = '../data/'
    #exp_data_dir = '../experimental_data/'
    #prepare_dress_sales_dataset()
    #generated_files_as_sequences(
    #    [data_dir + 'T_0-006_3_0-015_a.txt', data_dir + 'T_0-006_2_0-014_b.txt', data_dir + 'T_0-006_2_0-010_c.txt'],
    #    exp_data_dir + 'sequences.txt')
    
    start = timer()
    frequent_patterns_search(data_dir + 'test', 0.6, False)
    end = timer()
    print(end - start)
