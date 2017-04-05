#include "ScoreList.h"

ScoreList::ScoreList() {
    
}

bool ScoreList::add(unsigned long score) {
    if (score <= 100 && m_scores.insert(score)) {
        return true;
    }
    else
        return false;
}

bool ScoreList::remove(unsigned long score) {
    int found_index = m_scores.find(score);
    
    if (found_index >= 0) {
        m_scores.erase(found_index);
        return true;
    }
    else
        return false;
}

int ScoreList::size() const {
    return m_scores.size();
}

unsigned long ScoreList::minimum() const {
    if (size() == 0)
        return NO_SCORE;
    else {
        Sequence temp = m_scores;
        unsigned long min_score  = 0;
        temp.get(0,min_score);
        unsigned long some_score = 0;
        for (int i = 1; i < temp.size(); ++i) {
            temp.get(i, some_score);
            if (min_score > some_score)
                min_score = some_score;
        }
        return min_score;
    }
}

unsigned long ScoreList::maximum() const {
    if (size() == 0)
        return NO_SCORE;
    else {
        Sequence temp = m_scores;
        unsigned long max_score = 0;
        temp.get(0, max_score);
        unsigned long some_score = 0;
        for (int i = 1; i < temp.size(); ++i) {
            temp.get(i, some_score);
            if (max_score < some_score)
                max_score = some_score;
        }
        return max_score;
    }
}
