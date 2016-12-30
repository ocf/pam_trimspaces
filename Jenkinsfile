// check out code
stage name: 'check-out-code'

node('slave') {
    dir('src') {
        checkout scm
    }
    stash 'src'
}


// array.each doesn't work in jenkins, wtf
// https://issues.jenkins-ci.org/browse/JENKINS-26481
def dists = ['jessie', 'stretch']
for (def i = 0; i < dists.size(); i++) {
    def dist = dists[i]
    stage name: "build-${dist}"
    node('slave') {
        step([$class: 'WsCleanup'])
        unstash 'src'
        dir('src') {
            sh 'make clean'
            sh "make package_${dist}"
            sh "mv dist dist_${dist}"
            archiveArtifacts artifacts: "dist_${dist}/*"
        }
        stash 'src'
    }

    if (env.BRANCH_NAME == 'master') {
        stage name: "upload-${dist}"

        build job: 'upload-changes', parameters: [
            [$class: 'StringParameterValue', name: 'path_to_changes', value: "dist_${dist}/*.change"],
            [$class: 'StringParameterValue', name: 'dist', value: dist],
            [$class: 'StringParameterValue', name: 'job', value: env.JOB_NAME.replace('/', '/job/')],
            [$class: 'StringParameterValue', name: 'build_number', value: env.BUILD_NUMBER],
        ]
    }
}


// vim: ft=groovy
