print('Bienvenido al programa...')
persona = {'nombre':'','apellido':'','edad':0,'peso':0,'altura':0,'direccion':'','telefono':''}
for campo in persona:
    persona[campo] = input(f'Ingrese su {campo}: ').upper()
    imc = round(float(persona['peso'])/(float(persona['altura'])**2),2)
persona['IMC']=imc
def cat_imc(imc):
    if imc >= 0 and imc <= 18.5 :
        print ("bajo peso")
    elif imc >= 18.5 and imc <= 24.9 :
        print ("peso normal")
    elif imc >= 25.0 and imc <= 29.9:
        print ("sobre peso")
    elif imc >= 30 and imc <= 34.9 :
        print ("obesidad tipo I")
    elif imc >= 35.0 and imc <= 39.9:
        print ("obesidad tipo II")
    elif imc >= 40.00:
        print ("obesidad tipo III")   

cat_imc(imc)

imprimir = print
imprimir(persona)