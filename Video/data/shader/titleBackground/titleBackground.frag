#version 120
uniform vec2 resolution;
uniform float time;
out vec4 outputColor;
void main( void ) {
	vec2 p = gl_FragCoord.xy / resolution.x *2. + vec2(-1.,-.5);
	float radius = .5;
	//float height = sqrt(dot(vec3(radius, p), vec3(-radius, p)));

	float height = sqrt((dot(p,p))-dot(radius,radius))*sin(time);
	vec3 normal = normalize(vec3(p.x*cos(time),p.y*sin(time),height));

	float shad = dot(normal,vec3(-.4, .4, .9));
	gl_FragColor = vec4(shad,shad,shad, 1.);

}
