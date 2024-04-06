extends Node2D

signal finger_moved(finger: String, new_value: float)

@onready var pinky = $PinkySlider
@onready var ring = $RingSlider
@onready var middle = $MiddleSlider
@onready var index = $IndexSlider
@onready var thumb = $ThumbSlider

@onready var finger_sliders = {
	"pinky": pinky,
	"ring": ring,
	"middle": middle,
	"index": index,
	"thumb": thumb,
}

var finger_values = {
	"pinky": 0.0,
	"ring": 0.0,
	"middle": 0.0,
	"index": 0.0,
	"thumb": 0.0,
}

func _process(delta):
	for finger: String in finger_sliders:
		var new_value = finger_sliders[finger].slider_value
		if (new_value != finger_values[finger]):
			finger_moved.emit(finger, new_value)
			finger_values[finger] = new_value
