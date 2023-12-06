# MNISTRW

Read and convert the original MNIST dataset with C.

## MNIST Download

The kaggle page to MNIST Dataset is:

https://www.kaggle.com/datasets/hojjatk/mnist-dataset

The original MNIST repository is:

http://yann.lecun.com/exdb/mnist/

The only necessary and direct link to download is :

https://www.kaggle.com/datasets/hojjatk/mnist-dataset/download?datasetVersionNumber=1

The downloaded file is a archive.zip that when is uncompressed we something like this:


![alt text](/readme-resources/mnist-download-archive-content.png "Archive Content")

The files are in folders and also in the root. So, just consider one of them:

* t10k-images.idx3-ubyte

    10000 images for tests.

* t10k-labels.idx1-ubyte

    Labels for the 10000 test images.

* train-images.idx3-ubyte

    60000 images for training.

* train-labels.idx1-ubyte

    Labels for the 60000 training images.

## Labels File Structure

The labels file starts with 8 bytes and, after, each byte represents one label, at the same order of the corresponding image file.

Let's take t10k-labels.idx1-ubyte as example and open it with a binary editor:

![alt text](/readme-resources/beginning-test-labels-binary-view.png "Beginning of the test labels binary view")

The first 8 bytes are ignored, so, the value of byte at position 0x8, 9th byte, is 7 and it means that it is the label of the first image of the file t10k-images.idx3-ubyte, the second label is 2, then third is 1 and so on.

![alt text](/readme-resources/ending-test-labels-binary-view.png "Ending of the test labels binary view")

The last address is 0x2717 that is 10007 in decimal. The first address is 0, so, the total amount of bytes is 10008 and as we ignored the first 8 bytes, we have exactly 10000 bytes, each one representing one label to the respective image in t10k-images.idx3-ubyte.

## Images File Structure

The images file starts with 16 bytes and, after, every 784 bytes represents one image of 28x28 pixels.

Let's take t10k-images-idx3-ubyte as example and open it with a binary editor:

![alt text](/readme-resources/beginning-test-images-binary-view.png "Beginning of the test labels binary view")


![alt text](/readme-resources/ending-test-images-binary-view.png "Ending of the test labels binary view")

The last address is 0x77A10F that is 7840015 in decimal. The first address is 0, so, the total amount of bytes is 7840016 and as we ignored the first 16 bytes, we have exactly 7840000 bytes, each group of 784 bytes is a image of 28x28 pixels, so dividing 7840000 by 28, we have 280000 and dividing again by 28 we have 10000 that is the amount of images in the file.