import auxiliarymethods.datasets as dp
from auxiliarymethods.gnn_evaluation import gnn_evaluation
from gnn_baselines.gnn_architectures import GIN, GINE, GINEWithJK, GINWithJK


def main():
    num_reps = 2
    num_epochs = 2
    learning_rate = 0.01
    text_file = open("Output.txt", "w")    

    ### Without edge labels
    dataset = [["IMDB-BINARY", False], ["IMDB-MULTI", False]]

    results = []
    for d, use_labels in dataset:
        # Download dataset.
        dp.get_dataset(d)

        # GIN, dataset d, layers in [1:6], hidden dimension in {32,64,128}.
        acc, s_1, s_2 = gnn_evaluation(GIN, d, [1, 2, 3, 4, 5], [32, 64, 128], max_num_epochs=num_epochs, batch_size=64,
                                       start_lr=learning_rate, num_repetitions=num_reps, all_std=True)
        print(d + " " + "GIN\t [" + str(acc) + "]")
        results.append(d + " " + "GIN\t [" + str(acc) + "]")

        # GIN with jumping knowledge, dataset d, layers in [1:6], hidden dimension in {32,64,128}.
        acc, s_1, s_2 = gnn_evaluation(GINWithJK, d, [1, 2, 3, 4, 5], [32, 64, 128], max_num_epochs=num_epochs,
                                       batch_size=64,
                                       start_lr=learning_rate, num_repetitions=num_reps, all_std=True)
        print(d + " " + "GINWithJK\t [" + str(acc) + "]")
        results.append(d + " " + "GINWithJK\t [" + str(acc) + "]")


    for r in results:
        text_file.write(r + "\n")


    text_file.close()

if __name__ == "__main__":
    main()
