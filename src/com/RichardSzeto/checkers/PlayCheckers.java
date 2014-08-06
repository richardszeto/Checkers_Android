package com.RichardSzeto.checkers;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.view.Window;

public class PlayCheckers extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) 
	{
		super.onCreate(savedInstanceState);
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		setContentView(R.layout.activity_play_checkers);
	}
	
	public void onButtonClicked(View v)
	{
		switch(v.getId())
		{
			case R.id.onePlayerButton:
				break;
			
			case R.id.twoPlayerButton:
				break;
		}
	}
}
