package com.bignerdranch.android.geoquiz;

import android.app.Activity;
import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;


//AppCompatActivity is a subclass of the Activity class that provides compatibility support for older versions of android
public class QuizActivity extends AppCompatActivity {

    private static final String TAG = "QuizActivity"; //used to identify class for debugging
    private static final String KEY_INDEX = "index"; //a constant that will be the key for the key-value pair that will be stored in the bundle.

    private static final int REQUEST_CODE_CHEAT = 0; //a user-defined integer that is sent to the child activity inside startActivityForResult and then received back by the parent. It is used when an activity starts more than one type of child activity and needs to know who is reporting back.


    private Button mTrueButton; //after the button has a resource ID, you can now access it
    private Button mFalseButton; //after the button has a resource ID, you can now access it
    private Button mNextButton; //after the button has a resource ID, you can now access it
    private Button mCheatButton; //after the button has a resource ID, you can now access it
    private TextView mQuestionTextView; //A user interface element that displays text to the user. Access it with the resource ID

    //user created Question class where mQuestionBank is the var name and it holds an array of Question objects
    private Question[] mQuestionBank = new Question[] {
        new Question(R.string.question_australia, true),
        new Question(R.string.question_oceans, true),
        new Question(R.string.question_mideast, false),
        new Question(R.string.question_africa, false),
        new Question(R.string.question_americas, true),
        new Question(R.string.question_asia, true),
    };

    private int mCurrentIndex = 0; //sets a variable for the index that will be used for mQuestionBank
    private boolean mIsCheater; //variable that holds the value if the user cheated or not

    //A Bundle is a structure that maps string keys to values of certain limited types.
    @Override //@Override means that the method is overriding the parent class
    protected void onCreate(Bundle savedInstanceState) { //savedInstanceState is a Bundle object containing the activity's previously saved state
        super.onCreate(savedInstanceState); //must be used to inflate the UI. Called when the activity is starting. This is where most initialization should go
        Log.d(TAG, "onCreate(Bundle) called"); //used to log a message
        setContentView(R.layout.activity_quiz); //Set the activity content from a layout resource. The resource will be inflated, adding all top-level views to the activity

        if(savedInstanceState != null){ //if no data is being passed, then...
            mCurrentIndex = savedInstanceState.getInt(KEY_INDEX, 0); //getInt returns the value associated with the given key, or defaultValue if no mapping of the desired type exists for the given key.
        }

        mQuestionTextView = (TextView) findViewById(R.id.question_text_view); //associate the resource ID with the text view

        mTrueButton = (Button) findViewById(R.id.true_button); //associate the resource id button with the java button
        mTrueButton.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View v){
                checkAnswer(true);
            }
        });

        mFalseButton = (Button) findViewById(R.id.false_button);
        mFalseButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                checkAnswer(false);
            }
        });

        mNextButton = (Button) findViewById(R.id.next_button);
        mNextButton.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View v){
                mCurrentIndex = (mCurrentIndex + 1) % mQuestionBank.length;
                mIsCheater = false;
                updateQuestion();
            }
        });

        mCheatButton = (Button) findViewById(R.id.cheat_button);
        mCheatButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v){
                //start CheatActivity
                boolean answerIsTrue = mQuestionBank[mCurrentIndex].isAnswerTrue();
                Intent intent = CheatActivity.newIntent(QuizActivity.this, answerIsTrue);
                startActivityForResult(intent, REQUEST_CODE_CHEAT); //When you want to hear back from the child activity, you call this fActivity method
            }
        });

        updateQuestion();
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data){
        if(resultCode != Activity.RESULT_OK){
            return;
        }
        if(requestCode == REQUEST_CODE_CHEAT){
            if(data == null){
                return;
            }
            mIsCheater = CheatActivity.wasAnswerShown(data);
        }
    }

    @Override
    public void onStart(){
        super.onStart();
        Log.d(TAG, "onStart() called");
    }

    @Override
    public void onResume(){
        super.onResume();
        Log.d(TAG, "onResume() called");
    }

    @Override
    public void onPause(){
        super.onPause();
        Log.d(TAG, "onPause() called");
    }

    @Override
    public void onSaveInstanceState(Bundle savedInstanceState){
        super.onSaveInstanceState(savedInstanceState);
        Log.i(TAG, "onSaveInstanceState");
        savedInstanceState.putInt(KEY_INDEX, mCurrentIndex);
    }

    @Override
    public void onStop(){
        super.onStop();
        Log.d(TAG, "onStop() called");
    }

    @Override
    public void onDestroy(){
        super.onDestroy();
        Log.d(TAG, "onDestroy() called");
    }

    private void updateQuestion() {
        int question = mQuestionBank[mCurrentIndex].getTextResId();
        mQuestionTextView.setText(question);
    }

    private void checkAnswer(boolean userPressedTrue){
        boolean answerIsTrue = mQuestionBank[mCurrentIndex].isAnswerTrue();

        int messageResId = 0;

        if(mIsCheater) {
            messageResId = R.string.judgement_toast;
        }else {
            if (userPressedTrue == answerIsTrue) {
                messageResId = R.string.correct_toast;
            } else {
                messageResId = R.string.incorrect_toast;
            }
        }

        Toast.makeText(this, messageResId, Toast.LENGTH_SHORT).show();
    }
}
