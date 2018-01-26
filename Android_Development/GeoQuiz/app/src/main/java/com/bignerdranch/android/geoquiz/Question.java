package com.bignerdranch.android.geoquiz;

//holds two pieces of data: the question text and the question answer
public class Question {

    //question text. It is an integer because this variable will hold
    //a resource ID of a string resource
    private int mTextResId;

    private boolean mAnswerTrue;

    public Question(int textResId, boolean answerTrue){
        mTextResId = textResId;
        mAnswerTrue = answerTrue;
    }

    public int getTextResId() {
        return mTextResId;
    }

    public void setTextResId(int textResId) {
        mTextResId = textResId;
    }

    public boolean isAnswerTrue() {
        return mAnswerTrue;
    }

    public void setAnswerTrue(boolean answerTrue) {
        mAnswerTrue = answerTrue;
    }
}
