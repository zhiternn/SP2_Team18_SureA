struct Component
{
	float r, g, b;
	Component(float r = 0.1f, float g = 0.1f, float b = 0.1f)
	{
		Set(r, g, b);
	}
	void Set(float r, float g, float b)
	{
		this->r = r; 
		this->g = g; 
		this->b = g;
	}
};
struct Material
{
	Component kAmbient;
	Component kDiffuse;
	Component kSpecular;
	float kShininess;
	Material()
	{
		kAmbient.Set(0.5f, 0.5f, 0.5f);
		kDiffuse.Set(0.6f, 0.6f, 0.6f);
		kSpecular.Set(0.f, 0.f, 0.f);
		kShininess = 0.5f;
	}
	void SetToChrome()
	{
		kAmbient.Set(0.25f, 0.25f, 0.25f);
		kDiffuse.Set(0.4f, 0.4f, 0.4f);
		kSpecular.Set(0.774597f, 0.774597f, 0.774597f);
		kShininess = 76.8f;
	}
	void SetToPlastic()
	{
		kAmbient.Set(0.25f, 0.25f, 0.25f);
		kDiffuse.Set(0.4f, 0.4f, 0.4f);
		kSpecular.Set(0.774597f, 0.774597f, 0.774597f);
		kShininess = 76.8f;
	}
	void SetToPolishedSilver()
	{
		kAmbient.Set(0.23125f, 0.23125f, 0.23125);
		kDiffuse.Set(0.2775f, 0.2775f, 0.2775);
		kSpecular.Set(0.773911f, 0.773911f, 0.773911f);
		kShininess = 89.6f;
	}
	void SetToSilver()
	{
		kAmbient.Set(0.19225f, 0.19225f, 0.19225f);
		kDiffuse.Set(0.50754f, 0.50754f, 0.50754f);
		kSpecular.Set(0.508273f, 0.508273f, 0.508273f);
		kShininess = 51.2f;
	}
	void SetToArmorMaterial()
	{
		kAmbient.Set(0.5f, 0.5f, 0.5f);
		kDiffuse.Set(0.5f, 0.5f, 0.5f);
		kSpecular.Set(1.f, 1.f, 1.f);
		kShininess = 10.f;
	}
};