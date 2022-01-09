package com.example.moves_android

import android.graphics.drawable.ColorDrawable
import android.os.Bundle
import android.view.ViewGroup
import android.widget.Button
import android.widget.ImageView
import android.widget.RelativeLayout
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import androidx.core.content.ContextCompat
import androidx.core.view.setMargins
import com.example.moves_android.R.color.*
import com.example.moves_android.databinding.ActivityMainBinding


class MainActivity : AppCompatActivity() {
    private lateinit var binding: ActivityMainBinding
    private lateinit var ballBlue: ImageView
    private lateinit var ballGreen: ImageView
    private lateinit var ballRed: ImageView

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivityMainBinding.inflate(layoutInflater)
        val view = binding.root
        setContentView(view)

        createBalls()
        createMap()
        createButtons()
    }

    /**
     * Creates a sample map
     */
    private fun createMap () {
        // we want the following positions with these specific colors:

        // 1x3 -> green
        setBackgroundColor(1, 3, myGreen)
        addBall(ballGreen, 1, 2)

        // 2x2 -> blue
        setBackgroundColor(2, 2, myBlue)
        addBall(ballBlue, 2, 1)

        // 2x3 -> white
        setBackgroundColor(2, 3, white)

        // 3x3 -> red
        setBackgroundColor(3, 3, myRed)
        addBall(ballRed, 3, 2)
    }

    /**
     * Create the balls
     */
    private fun createBalls () {
        // Create ball blue
        ballBlue = ImageView(this)
        ballBlue.setImageResource(R.drawable.circle_blue)

        // Create ball green
        ballGreen = ImageView(this)
        ballGreen.setImageResource(R.drawable.circle_green)

        // Create ball red
        ballRed = ImageView(this)
        ballRed.setImageResource(R.drawable.circle_red)
    }

    /**
     * Add a specific ball to a specific location (x,y)
     */
    private fun addBall(ball: ImageView, row: Int, col: Int) {
        // if ball already has a parent, we need to remove it first
        ball.apply {
            if (parent != null) {
                (ball.parent as ViewGroup).removeView(ball)
            }
        }

        val params = RelativeLayout.LayoutParams(
            RelativeLayout.LayoutParams.WRAP_CONTENT,
            RelativeLayout.LayoutParams.WRAP_CONTENT
        )
        params.addRule(RelativeLayout.CENTER_HORIZONTAL)
        params.addRule(RelativeLayout.CENTER_VERTICAL)
        params.setMargins(50)

        getRelativeLayout(row, col)?.addView(ball, params)

    }

    /**
     * Create buttons listeners
     */
    private fun createButtons() {
        // get reference to button
        val btnLeft = findViewById<Button>(R.id.buttonLeft)
        // set on-click listener
        btnLeft.setOnClickListener {
            moveLeft(ballBlue)
            moveLeft(ballGreen)
            moveLeft(ballRed)
        }

        // get reference to button
        val btnUp = findViewById<Button>(R.id.buttonUp)
        // set on-click listener
        btnUp.setOnClickListener {
            moveUp(ballBlue)
            moveUp(ballGreen)
            moveUp(ballRed)
        }

        // get reference to button
        val btnDown = findViewById<Button>(R.id.buttonDown)
        // set on-click listener
        btnDown.setOnClickListener {
            moveDown(ballBlue)
            moveDown(ballGreen)
            moveDown(ballRed)
        }

        // get reference to button
        val btnRight = findViewById<Button>(R.id.buttonRight)
        // set on-click listener
        btnRight.setOnClickListener {
            moveRight(ballBlue)
            moveRight(ballGreen)
            moveRight(ballRed)
        }
    }

    /**
     * Move a ball to the right
     */
    private fun moveRight(ball: ImageView) {
        ball.apply {
            if (parent != null) {
                val pair = getCoordinatesFromRelativeLayout(parent as RelativeLayout)
                if (pair != null) {
                    val (row, col) = pair
                    updateBall(ball, row,col+1)
                }
            }
        }
    }

    /**
     * Move a ball to the left
     */
    private fun moveLeft(ball: ImageView) {
        ball.apply {
            if (parent != null) {
                val pair = getCoordinatesFromRelativeLayout(parent as RelativeLayout)
                if (pair != null) {
                    val (row, col) = pair
                    updateBall(ball, row,col-1)
                }
            }
        }
    }

    /**
     * Move a ball up
     */
    private fun moveUp(ball: ImageView) {
        ball.apply {
            if (parent != null) {
                val pair = getCoordinatesFromRelativeLayout(parent as RelativeLayout)
                if (pair != null) {
                    val (row, col) = pair
                    updateBall(ball, row-1, col)
                }
            }
        }
    }

    /**
     * Move a ball down
     */
    private fun moveDown(ball: ImageView) {
        ball.apply {
            if (parent != null) {
                val pair = getCoordinatesFromRelativeLayout(parent as RelativeLayout)
                if (pair != null) {
                    val (row, col) = pair
                    updateBall(ball, row+1, col)
                }
            }
        }
    }

    private fun setBackgroundColor(row: Int, col: Int, newColor: Int) {
        val rl = getRelativeLayout(row,col)
        if (rl != null) {
            with(rl) {
                setBackgroundColor(ContextCompat.getColor(context, newColor))
            }
        }
    }
    private fun isBackgroundColorWhite(rl: RelativeLayout): Boolean {
        if (rl.background is ColorDrawable) {
            val colorId = (rl.background as ColorDrawable).color
            val hexColor = String.format("#%06X", 0xFFFFFF and colorId)
            return hexColor == "#FFFFFF"
        }
        return false
    }
    private fun getRelativeLayout(row: Int, col: Int): RelativeLayout? {
        if (row == 1) {
            if (col == 1) return binding.base1x1
            if (col == 2) return binding.base1x2
            if (col == 3) return binding.base1x3
        } else if (row == 2) {
            if (col == 1) return binding.base2x1
            if (col == 2) return binding.base2x2
            if (col == 3) return binding.base2x3
        } else if (row == 3) {
            if (col == 1) return binding.base3x1
            if (col == 2) return binding.base3x2
            if (col == 3) return binding.base3x3
        }
        return null
    }
    private fun getCoordinatesFromRelativeLayout(rl: RelativeLayout): Pair<Int, Int>? {
        val id = (rl as ViewGroup).id
        val resourceName = resources.getResourceName(id)

        when {
            resourceName.equals("com.example.moves_android:id/base1x1") -> {
                return Pair(1,1)
            }
            resourceName.equals("com.example.moves_android:id/base1x2") -> {
                return Pair(1,2)
            }
            resourceName.equals("com.example.moves_android:id/base1x3") -> {
                return Pair(1,3)
            }
            resourceName.equals("com.example.moves_android:id/base2x1") -> {
                return Pair(2,1)
            }
            resourceName.equals("com.example.moves_android:id/base2x2") -> {
                return Pair(2,2)
            }
            resourceName.equals("com.example.moves_android:id/base2x3") -> {
                return Pair(2,3)
            }
            resourceName.equals("com.example.moves_android:id/base3x1") -> {
                return Pair(3,1)
            }
            resourceName.equals("com.example.moves_android:id/base3x2") -> {
                return Pair(3,2)
            }
            resourceName.equals("com.example.moves_android:id/base3x3") -> {
                return Pair(3,3)
            }
            else -> return null
        }
    }
    private fun updateBall(ball:ImageView, row: Int, col: Int) {
        val rl = getRelativeLayout(row,col)
        if (rl != null && !isBackgroundColorWhite(rl)) {
            (ball.parent as ViewGroup).removeView(ball)
            rl.addView(ball)
        }
    }
}