from django.db import models

# Create your models here.
class Data(models.Model):
    timestamp = models.TimeField(auto_now_add=True)
    temperature = models.FloatField()
    level = models.FloatField()

    class meta:
        ordering = ['created']
