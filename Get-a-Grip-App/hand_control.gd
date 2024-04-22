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
		var finger_slider = (finger_sliders[finger] as FingerSlider)
		var new_value = finger_slider.slider_value
		if (new_value != finger_values[finger]):
			var cooldown_timer = (finger_slider.get_node("CooldownTimer") as Timer)
			if cooldown_timer.is_stopped():
				finger_moved.emit(finger, new_value)
				cooldown_timer.start()
				finger_values[finger] = new_value
