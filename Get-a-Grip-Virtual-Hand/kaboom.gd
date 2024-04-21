extends Sprite3D

@onready var animation_player = $AnimationPlayer


func boom():
	show()
	animation_player.play("explode")
	await animation_player.animation_finished
	await get_tree().create_timer(2).timeout
	get_tree().reload_current_scene()
