Compressing text
-
1. Iterate over text and count occurrences of each character.
2. Create priority queue of characters, ordered by frequency (where lowest frequency is highest priority).
3. Build Huffman tree from priority queue.
4. Traverse Huffman tree to populate a map of character codes.
5. Iterate over text again to encode each character using codes map.
6. To decode, iterate over encoding while traversing the Huffman tree.


Building a Huffman Tree
-
1. Enqueue all letters in a priority queue with lowest frequency letter at the front
2. If the queue contains a single node, make that node the root of the tree and dequeue it, and we are done.  Stop the process.
3. Make a new node with a dummy character (the characters in the text will only be represented by leaf nodes, so it does not matter what this character is).
4. Dequeue the first node and make it the left node of the new node.
5. Dequeue the first node again and make it the right node of the new node.
6. Set the frequency of the new node to the sum of the frequencies of its left and right nodes.
7. Enqueue the new node and return to step 2.


Encoding a string
-
1. Initialize an encoding map.
2. Traverse the huffman tree from the root with an empty string (the code).
3. If there’s a left child, go left and append “0” to the code.
4. If there’s a right child, go right and append “1” to the code.
5. Once you hit a leaf, add the character at the left and the code into the map.
6. Continue adding to the encoding map until you’ve traversed the whole tree.
7. terate through the input string. For each letter, find it’s encoding and append it to the output string.

Decoding a string
-
1. Initialize a temp variable pointing to the root of the huffman tree.
2. Iterate through the encoded string.
3. If it’s a “0”, set temp to temp->left. Else set temp to temp->right.
4. If temp is now a leaf, append that character to our output string and reset temp to root.
5. Go back to step 2

