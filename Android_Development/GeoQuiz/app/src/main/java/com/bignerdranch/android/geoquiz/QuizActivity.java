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

    private static final String TAG = "QuizActivity"; //used to identify the current class for debugging
    private static final String KEY_INDEX = "index"; //a constant that will be the key for the key-value pair that will be stored in the bundle.

    private static final int REQUEST_CODE_CHEAT = 0; //a user-defined integer that is sent to the child activity inside
    //startActivityForResult and then received back by the parent. It is used when an activity starts more than one type of child activity and needs to know who is reporting back.
    //Use startActivityForResult to hear back from the child activity

    private Button mTrueButton; //after the button has a resource ID, you will be able to access it
    private Button mFalseButton; //after the button has a resource ID, you will be able to access it
    private Button mNextButton; //after the button has a resource ID, you will be able to access it
    private Button mCheatButton; //after the button has a resource ID, you will be able to access it
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
    //the onCreate method is called after the activity instance is created but before it is put on screen
	//an activity overrides onCreate to prepare the specifics of its UI
    protected void onCreate(Bundle savedInstanceState) { //savedInstanceState is a Bundle object containing the activity's previously saved state
        super.onCreate(savedInstanceState); //must be used to inflate the UI. Called when the activity is starting. This is where most initialization should go
        Log.d(TAG, "onCreate(Bundle) called"); //used to log a message
        setContentView(R.layout.activity_quiz); //Set the activity content from a layout resource. The resource will be inflated, adding all top-level views to the activity

        if(savedInstanceState != null){ //if data is being passed from a previous state, then...
            mCurrentIndex = savedInstanceState.getInt(KEY_INDEX, 0); //getInt returns the value associated with the given key, or defaultValue if no mapping of the desired type exists for the given key.
        }

        mQuestionTextView = (TextView) findViewById(R.id.question_text_view); //associate the resource ID with the text view

        mTrueButton = (Button) findViewById(R.id.true_button); //associate the resource id button with the java button
        //creates an anonymous (nameless) inner class which implements the interface's single method onClick(View)
        mTrueButton.setOnClickListener(new View.OnClickListener(){
            @Override
            //checkAnswer is a custom method defined below which checks the answer and returns the appropriate toast
            public void onClick(View v){
                checkAnswer(true);
            }
        });

        mFalseButton = (Button) findViewById(R.id.false_button); //associate the resource id button with the java button
        //creates an anonymous (nameless) inner class which implements the interface's single method onClick(View)
        mFalseButton.setOnClickListener(new View.OnClickListener() {
            @Override
            //checkAnswer is a custom method defined below which checks the answer and returns the appropriate toast
            public void onClick(View v) {
                checkAnswer(false);
            }
        });

        mNextButton = (Button) findViewById(R.id.next_button); //associate the resource id button with the java button
        //creates an anonymous (nameless) inner class which implements the interface's single method onClick(View)
        mNextButton.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View v){
                mCurrentIndex = (mCurrentIndex + 1) % mQuestionBank.length;//increases mCurrentIndex to represent the next question in the bank
                mIsCheater = false; //resets mIsCheater to false
                updateQuestion(); //custom method defined below which fetches the next question from the bank
            }
        });

        mCheatButton = (Button) findViewById(R.id.cheat_button); //associates the resource id button with the java button
        //creates an anonymous (nameless) inner class which implements the interface's single method onClick(View)
        mCheatButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v){
                //start CheatActivity
                boolean answerIsTrue = mQuestionBank[mCurrentIndex].isAnswerTrue();
                Intent intent = CheatActivity.newIntent(QuizActivity.this, answerIsTrue);//creates the intent object which defines which activity to start
                startActivityForResult(intent, REQUEST_CODE_CHEAT); //starts the activity
                // When you want to hear back from the child activity, you call the above Activity method
            }
        });

        updateQuestion(); //custom method defined below which fetches the next question from the bank
    }

    @Override
    //this method is called when the user presses the back button from CheatActivity.
    //The request code is from startActivityForResult from above
    //The resultCode is one of two predefined constants: RESULT_OK or RESULT_CANCELLED. Setting
    //result codes is useful when the parent needs to take different action depending on how the
    //child activity finished.
    protected void onActivityResult(int requestCode, int resultCode, Intent data){
        if(resultCode != Activity.RESULT_OK){
            return;
        }
        if(requestCode == REQUEST_CODE_CHEAT){ //if the back button was hit from the CheatActivity...
            if(data == null){
                return;
            }
            mIsCheater = CheatActivity.wasAnswerShown(data); //sets this variable depending on if the user cheated
        }
    }

    //the following five methods display logigng informaiton depending on the Activity's lifecycle
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
    //saves data across a runtime configuration change, like rotation
    public void onSaveInstanceState(Bundle savedInstanceState){
        super.onSaveInstanceState(savedInstanceState);
        Log.i(TAG, "onSaveInstanceState");
        savedInstanceState.putInt(KEY_INDEX, mCurrentIndex); //this demonstrates a Bundle in action
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

    //sets the new question by calling the getTextResId method from the Question.java class and then
    //using the setText method of the TextView class
    private void updateQuestion() {
        int question = mQuestionBank[mCurrentIndex].getTextResId();
        mQuestionTextView.setText(question);
    }

    //checks if the answer is true or not and outputs the correct toast
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
