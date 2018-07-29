#!/usr/bin/env groovy

pipeline {
  agent any

  environment {
    scannerHome = tool 'sonarscanner303778'
  }

  stages {
    stage('Build') {
      steps {
        sh 'cmake . -DCMAKE_BUILD_TYPE=DEBUG 2>&1'
        sh 'make all 2>&1 > build.log'
      }
    }

    stage('Analysis') {
      steps {
        sh 'cppcheck --enable=all  --suppress=missingIncludeSystem --xml --xml-version=2 src 2> cppcheck.xml'

        withSonarQubeEnv("r2d2") {
          sh "${scannerHome}/bin/sonar-scanner -Dproject.settings=sonar-project.properties -Dsonar.branch=${env.BRANCH_NAME}"
        }
        script {
          timeout(time: 1, unit: 'HOURS') {
            def qg = waitForQualityGate()
            if (qg.status != 'OK') {
              error 'Sonarqube failed.'
            }
          }
        }
      }
    }
  }
}
