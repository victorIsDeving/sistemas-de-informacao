import numpy as np
from training import training, feed_forward, confusion_matrix
from report import markdown_report, dict_resume

data_path = "C:/sistemas-informacao/ia-ACH2016/ep1-mlp/COMPLETO/X.npy"
target_path = "C:/sistemas-informacao/ia-ACH2016/ep1-mlp/COMPLETO/Y_classe.npy"
test = "04"
output_file = f"report{test}.md"
output_dir = f"test{test}"
output_loc = f"outputs/{output_dir}/"
hidden_perceptrons = 80
output_perceptrons = 26  # len(targets[0]), total classes
learn_rate = 0.5
threshold = 0.7
act_func = 'sigmoid-binary'
early_stop_bool = True
early_stop_patience = 15
cross_validation_bool = False
cross_validation_folds = 5

# inputs
data = np.load(data_path)
input_data = np.random.rand(len(data), 120)
for i, row in enumerate(data):
    input_data[i] = row.flatten()

# targets
target = np.load(target_path)
input_target = np.random.rand(len(target), 26)
for i, row in enumerate(target):
    input_target[i] = row.flatten()

# evening classes between training and testing
alphabet_repetition = len(input_data) / output_perceptrons
if cross_validation_bool:
    # training data and testing data, +- 80/20
    split_index = int(alphabet_repetition * 1 / cross_validation_folds) * output_perceptrons
    # save every fold results
    start_weights_list = []
    final_weights_list = []
    epoch_counters = []
    validation_losses = []
    results = []

    for i in range(cross_validation_folds):
        # test data
        test_data = input_data[split_index * i:split_index * (i + 1)]
        test_target = input_target[split_index * i:split_index * (i + 1)]
        # train data
        train_data = np.concatenate((input_data[:split_index * i], input_data[split_index * (i + 1):]), axis=0)
        train_target = np.concatenate((input_target[:split_index * i], input_target[split_index * (i + 1):]), axis=0)
        # training
        training_results = training(train_data, train_target,
                                    learn_rate, hidden_perceptrons,
                                    early_stop_bool, act_func, early_stop_patience)
        # testing
        test_results = feed_forward(test_data, test_target,
                                    training_results[1][0], training_results[1][1],
                                    hidden_perceptrons, output_perceptrons, act_func)

        start_weights_list.append(training_results[0])
        final_weights_list.append(training_results[1])
        epoch_counters.append(training_results[2])
        validation_losses.append(training_results[3])
        results.append(test_results[1])

    avg_start_weights = np.mean(start_weights_list, axis=0)
    avg_final_weights = np.mean(final_weights_list, axis=0)
    avg_epoch_counter = np.mean(epoch_counters)
    avg_validation_loss = np.mean(validation_losses)
    avg_results = np.mean(results, axis=0)

else:  # simple holdout
    # Training data and testing data, +- 80/20
    split_index = int(alphabet_repetition * 0.8) * output_perceptrons
    # test data
    test_target = input_target[split_index:]
    test_data = input_data[split_index:]
    # train data
    train_data = input_data[:split_index]
    train_target = input_target[:split_index]
    # training
    training_results = training(train_data, train_target,
                                learn_rate, hidden_perceptrons,
                                early_stop_bool, act_func, early_stop_patience)
    # testing
    testing_results = feed_forward(test_data, test_target,
                                   training_results[1][0], training_results[1][1],
                                   hidden_perceptrons, output_perceptrons, act_func)
    all_info = dict_resume(hidden_perceptrons, output_perceptrons,
                           learn_rate, act_func, early_stop_bool, early_stop_patience,
                           training_results[4], threshold,
                           cross_validation_bool, cross_validation_folds,
                           training_results, testing_results, output_loc)
    confusion_matrix = confusion_matrix(test_target, testing_results[1], output_perceptrons, threshold)
    markdown_report(f"{output_loc}/{output_file}", all_info, confusion_matrix)
