#include <iostream>
#include <climits>
#include "vector"
#include "unordered_map"
using namespace std;

class Solution {
public:
    int lengthOfLastWord(string s) {
        int currCount = 0;
        int lastWordCount = 0;
        for (char c: s) {
            if (c == ' ') {
                lastWordCount = currCount;
                currCount = 0;
            } else {
                currCount++;
            }
        }
        if (currCount > 0) {
            lastWordCount = currCount;
        }
        return currCount;
    }

    /*Given an array of positive numbers and a positive number ‘k,’ find the maximum sum of any contiguous subarray of size ‘k’.*/
    int MaximumSumSubarrayOfSizeK(vector<int>& vec, int k) {
        int currSum = 0;
        int maxSum = 0;
        for (int i = 0; i < k; i++) {
            currSum += vec[i];
        }
        maxSum = currSum;
        for (int i = k; i < vec.size(); i++) {
            currSum += vec[i];
            currSum -= vec[i-k];
            if (currSum > maxSum) {
                maxSum = currSum;
            }
        }
        return maxSum;
    }
    /**Given an array of positive numbers and a positive number ‘S,’ find the length of the smallest contiguous subarray whose sum is greater than or equal to ‘S’.
     * Return 0 if no such subarray exists. */
    static int findMinSubArray(int S, const vector<int>& arr) {
        int windowSum = 0, minLength = INT_MAX, windowStart = 0, sum = 0;
        for (int windowEnd = 0; windowEnd < arr.size(); windowEnd++) {
            sum += arr[windowEnd];

            while (sum >= S) {
                minLength = min(minLength, (1 + windowEnd - windowStart));
                sum -= arr[windowStart];
                windowStart++;
            }
        }
        if (minLength < INT_MAX) {
            return minLength;
        } else {
            return 0;
        }
    }

    int LongestSubstringWithKDistinctCharacters(string s, int k) {
        unordered_map<char, int> freqMap;
        int maxLength = 0;
        int start = 0;
        for (int end = 0; end < s.length(); end++) {
            freqMap[s[end]]++;
            while (freqMap.size() > k) {
                freqMap[s[start]]--;
                if (freqMap[s[start]] == 0) {
                    freqMap.erase(s[start]);
                }
                start++;
            }
            maxLength = max(maxLength, (1 + end - start));
        }
        return maxLength;
    }

    int FruitsIntoBaskets(vector<char> vec) {
        int start = 0;
        unordered_map<char, int> freqMap;
        for (int end = 0; end < vec.size(); end++) {
            freqMap[vec[end]]++;
            while (freqMap.size() > 2) {
                freqMap[vec[start]]--;
                if (freqMap[vec[start]] == 0) {
                    freqMap.erase(vec[start]);
                }
                start++;
            }
        }
        int total = 0;
        for (auto it = freqMap.begin(); it != freqMap.end(); it++) {
            total += it->second;
        }
        return total;
    }

    int LongestSubStringWithDistinctCharacters(string s) {
        int start = 0;
        int maxim = 0;
        unordered_map<char, int> freqMap;

        for (int end = 0; end < s.length(); end++) {
            freqMap[s[end]]++;
            while (freqMap[s[end]] > 1) {
                freqMap[s[start]]--;
                if (freqMap[s[start]] == 0) {
                    freqMap.erase(s[start]);
                }
                start++;
            }
            maxim = max(maxim, (1 + end - start));
        }
        return maxim;
    }

    static int findLength(const string &str, int k) {
        int windowStart = 0, maxRepeating = 0;
        int maxLength = 0;
        unordered_map<char, int> freqMap;

        for (int windowEnd = 0; windowEnd < str.length(); windowEnd++) {
            freqMap[str[windowEnd]]++;
            maxRepeating = max(maxRepeating, freqMap[str[windowEnd]]);


            if (windowEnd - windowStart + 1 - maxRepeating > k) {
                freqMap[str[windowStart]]--;
                windowStart++;
            }

            maxLength = max(maxLength, windowEnd - windowStart + 1);

        }
        return maxLength;
    }

    static int findLengthOfOnesWithKReplacement(vector<int> vec, int k) {
        int windowStart = 0;
        int maxLength = 0;
        unordered_map<int,int> freqMap;
        for (int windowEnd = 0; windowEnd < vec.size(); windowEnd++) {
            freqMap[vec[windowEnd]]++;

            while (freqMap[0] > k) {
                freqMap[vec[windowStart]]--;
                windowStart++;
            }

            maxLength = max(maxLength, freqMap[1] + freqMap[0]);
        }
        return maxLength;

    }

    bool findPermInString(string input, string pattern) {
        int windowStart = 0;
        int charMatch = 0;
        unordered_map<char, int> freqMap;

        for (int i = 0; i < pattern.length(); i++) {
            freqMap[pattern[i]]++;
        }
        for (int windowEnd = 0; windowEnd < input.length(); windowEnd++) {
            if (freqMap.find(input[windowEnd]) != freqMap.end()) {
                freqMap[input[windowEnd]]--;
                if (freqMap[input[windowEnd]] == 0) {
                    charMatch++;
                }
            }

            if (charMatch == freqMap.size()) {
                return true;
            }

            if (windowEnd >= pattern.length() - 1) {
                if (freqMap.find(input[windowStart]) != freqMap.end()) {
                    if (freqMap[input[windowStart]] == 0) {
                        charMatch--;
                    }
                    freqMap[input[windowStart]]++;
                }
                windowStart++;
            }

        }
        return false;
    }


    vector<int> findAllAnagramsOfPatternInString(string str, string pattern) {
        int windowStart = 0;
        int matched = 0;
        vector<int> anagramInds;
        unordered_map<char, int> charFrequencyMap;
        for (int i = 0; i < pattern.length(); i++) {
            charFrequencyMap[pattern[i]]++;
        }
        for (int windowEnd = 0; windowEnd < str.length(); windowEnd++) {
            char rightChar = str[windowEnd];
            // decrement the frequency of the matched character
            if (charFrequencyMap.find(rightChar) != charFrequencyMap.end()) {
                charFrequencyMap[rightChar]--;
                if (charFrequencyMap[rightChar] == 0) {
                    matched++;
                }
            }

            if (matched == charFrequencyMap.size()) {
                anagramInds.push_back(windowStart);
            }

            if (windowEnd >= pattern.length() - 1) {
                if (charFrequencyMap.find(str[windowStart]) != charFrequencyMap.end()) {
                    if (charFrequencyMap[str[windowStart]] == 0) {
                        matched--;
                    }
                    charFrequencyMap[str[windowStart]]++;
                }
                windowStart++;
            }

        }

        for (int i = 0; i < anagramInds.size(); i++) {
            cout << anagramInds[i] << ", ";
        }

        return anagramInds;
    }


    static vector<int> findStringAnagrams(const string &str, const string &pattern) {
        int windowStart = 0, matched = 0;
        unordered_map<char, int> charFrequencyMap;
        for (auto chr : pattern) {
            charFrequencyMap[chr]++;
        }

        vector<int> resultIndices;
        // our goal is to match all the characters from the map with the current window
        for (int windowEnd = 0; windowEnd < str.length(); windowEnd++) {
            char rightChar = str[windowEnd];
            // decrement the frequency of the matched character
            if (charFrequencyMap.find(rightChar) != charFrequencyMap.end()) {
                charFrequencyMap[rightChar]--;
                if (charFrequencyMap[rightChar] == 0) {
                    matched++;
                }
            }

            if (matched == (int)charFrequencyMap.size()) {  // have we found an anagram?
                resultIndices.push_back(windowStart);
            }

            if (windowEnd >= pattern.length() - 1) {  // shrink the window
                char leftChar = str[windowStart++];
                if (charFrequencyMap.find(leftChar) != charFrequencyMap.end()) {
                    if (charFrequencyMap[leftChar] == 0) {
                        matched--;  // before putting the character back, decrement the matched count
                    }
                    // put the character back
                    charFrequencyMap[leftChar]++;
                }
            }
        }

        for (int i = 0; i < resultIndices.size(); i++) {
            cout << resultIndices[i] << ", ";
        }

        return resultIndices;
    }

    string findSmallestSubstringWithPattern(string input, string pattern) {
        int windowStart = 0, matches = 0;
        int minLength = INT_MAX;
        string result = input;
        unordered_map<char, int> patternChars;
        for (int i = 0; i < pattern.length(); i++) {
            patternChars[pattern[i]]++;
        }
        for (int windowEnd = 0; windowEnd < input.length(); windowEnd++) {
            if (patternChars.find(input[windowEnd]) != patternChars.end()) {
                patternChars[input[windowEnd]]--;
                if (patternChars[input[windowEnd]] == 0) {
                    matches++;
                }
            }

            if (matches == patternChars.size()) {
                while (matches == patternChars.size()) {
                    //If the new minimum length is smaller than previous, find new minimum
                    if ((windowEnd - windowStart + 1) < result.length()) {
                        result = input.substr(windowStart, (windowEnd - windowStart + 1));
                    }
                    if (patternChars.find(input[windowStart]) != patternChars.end()) {
                        if (patternChars[input[windowStart]] == 0) {
                            matches--;
                        }
                        patternChars[input[windowStart]]++;
                    }
                    windowStart++;
                }
            }
        }
        cout << result << endl;
        return result;
    }

    static vector<int> findWordConcatenation(const string &str,
                                             const vector<string> &words) {
        unordered_map<string, int> wordFrequencyMap;
        for (auto word : words) {
            wordFrequencyMap[word]++;
        }

        vector<int> resultIndices;
        int wordsCount = words.size(), wordLength = words[0].length();

        for (int i = 0; i <= int(str.length()) - wordsCount * wordLength; i++) {
            unordered_map<string, int> wordsSeen;
            for (int j = 0; j < wordsCount; j++) {
                int nextWordIndex = i + j * wordLength;
                // get the next word from the string
                string word = str.substr(nextWordIndex, wordLength);
                if (wordFrequencyMap.find(word) ==
                    wordFrequencyMap.end()) {  // break if we don't need this word
                    break;
                }

                wordsSeen[word]++;  // add the word to the 'wordsSeen' map

                // no need to process further if the word has higher frequency than required
                if (wordsSeen[word] > wordFrequencyMap[word]) {
                    break;
                }

                if (j + 1 == wordsCount) {  // store index if we have found all the words
                    resultIndices.push_back(i);
                }
            }
        }

        return resultIndices;
    }

};


int main() {
    vector<int> ex{0, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1};
    vector<char> exChar{'A', 'B', 'C', 'B', 'B', 'C'};
    vector<string> words{"cat", "fox"};
    Solution A;
    A.findWordConcatenation("catfoxcat", words);
    return 0;
}
