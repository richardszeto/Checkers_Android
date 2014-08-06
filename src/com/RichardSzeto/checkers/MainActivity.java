package com.RichardSzeto.checkers;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.Window;

public class MainActivity extends Activity 
{

	@Override
	protected void onCreate(Bundle savedInstanceState) 
	{
		super.onCreate(savedInstanceState);
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		setContentView(R.layout.activity_main);
	}
	
	public void onButtonClicked(View v)
	{
		switch(v.getId())
		{
			case R.id.playCheckersButton:
				Intent i = new Intent(getApplicationContext(), PlayCheckers.class);
				startActivity(i);
				break;
				
			case R.id.changeSettingsButton:
				break;
		}
	}
}
