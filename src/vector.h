//__________________________________________________________________________________________________
Vertex add( const Vertex v, const Vertex w, int D ) {
	int i;
	Vertex m;
	for ( i = 0; i < D; i++ ) {
		m.x[i] = v.x[i] + w.x[i];
	}
	return m;
}

Vertex sub( const Vertex* v, const Vertex* w ) {
	int i;
	Vertex m;
	for ( i = 0; i < dim; i++ ) {
		m.x[i] = v->x[i] - w->x[i];
	}
	return m;
}

Vertex prod( const double a, const Vertex* v ) {
	int i;
	Vertex p;
	for ( i = 0; i < dim; i++ ) {
		p.x[i] = a * v->x[i];
	}
	return p;
}

double scalar( const Vertex* v, const Vertex* w ) {
	int i;
	double s = 0.0;
	for ( i = 0; i < dim; i++ ) {
		s += v->x[i] * w->x[i];
	}
	return s;
}

double norm( const Vertex* v ) {
	int i;
	double s = 0.0;
	for ( i = 0; i < dim; i++ ) {
		s += v->x[i] * v->x[i];
	}
	return sqrt(s);
}

