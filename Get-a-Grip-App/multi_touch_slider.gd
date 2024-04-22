class_name FingerSlider extends Path2D

@onready var thumb = $Thumb
@onready var thumb_button = $Thumb/ThumbButton
@onready var animate = $AnimationPlayer

var _current_touch_index = -1

var slider_value: float:
	get:
		return thumb.progress_ratio

func _ready():
	thumb_button.position = thumb_button.texture_normal.get_size() / -2

func _input(event):
	if event is InputEventScreenTouch:
		call_deferred("check_press", event)
	if event is InputEventScreenDrag and event.index == _current_touch_index:
		set_slider(event)
		get_viewport().set_input_as_handled()

func check_press(event: InputEventScreenTouch):
	if thumb_button.is_pressed() and event.is_pressed() and _current_touch_index == -1:
		_current_touch_index = event.index
		get_viewport().set_input_as_handled()
		animate.play("pressed")
	elif not event.is_pressed() and _current_touch_index == event.index:
		_current_touch_index = -1
		animate.play_backwards("pressed")

func set_slider(event: InputEventScreenDrag):
	var new_offset = curve.get_closest_offset(to_local(event.position))
	thumb.progress = new_offset
	var label = thumb.get_node_or_null("Label")
	if label is Label:
		label.text = "%f" % thumb.progress_ratio
	
