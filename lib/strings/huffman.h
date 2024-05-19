#pragma once

#include <lib/common.h>

/**
 * Usage:
 * https://codesprintla24.kattis.com/contests/codesprintla24open/submissions/13660055
 * 
 * using namespace huffman;
 * // build a node
 * vector<double> freq = {0.1, 0.2, 0.3};
 * HuffmanNode * node = buildHuffmanTree(freq);
 * 
 * ...
 * delete node;
*/
namespace huffman {
    // A Huffman tree node
    struct HuffmanNode {
        double freq;           // Frequency (probability) of the character
        HuffmanNode *left, *right; // Left and right child

        HuffmanNode(double freq_) {
            left = right = nullptr;
            this->freq = freq_;
        }
        
        virtual ~HuffmanNode() {
            if (this->left != nullptr) {
                delete this->left;
                delete this->right;
            }
        }
    };

    // For comparison of two heap nodes (needed in min heap)
    struct compare {
        bool operator()(HuffmanNode* l, HuffmanNode* r) {
            return (l->freq > r->freq);
        }
    };

    // Function to build a Huffman Tree and return its root
    HuffmanNode* buildHuffmanTree(const vector<double>& freq) {
        priority_queue<HuffmanNode*, vector<HuffmanNode*>, compare> minHeap;
        for (double f : freq)
            minHeap.push(new HuffmanNode(f));

        while (minHeap.size() != 1) {
            HuffmanNode* left = minHeap.top(); minHeap.pop();
            HuffmanNode* right = minHeap.top(); minHeap.pop();

            HuffmanNode* top = new HuffmanNode(left->freq + right->freq);
            top->left = left;
            top->right = right;

            minHeap.push(top);
        }

        return minHeap.top();
    }
} // namespace huffman

