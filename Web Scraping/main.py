from bs4 import BeautifulSoup

with open('home.html', 'r') as html_file: #html_file is the variable name asssigned to do the function
    content = html_file.read()
    
    #creating an instance of beautiful soup
    soup = BeautifulSoup(content, 'lxml') #pass become to string
#    courses_html_tags = soup.find_all('h5')
#    for course in courses_html_tags:
#        print(course.text)

    course_card = soup.find_all('div', class_='card') #it will relate to the class of the html attribute
    for course in course_card:
        course_name = course.h5.text #save all the related txt into the variable
        course_price = course.a.text.split()[2]

        print(f'{course_name} costs {course_price}')
